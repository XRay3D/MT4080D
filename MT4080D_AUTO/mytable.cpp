#include "mytable.h"
#include "mymodel.h"

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QClipboard>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollBar>
#include <QSettings>
#include <QTimer>

MyTable::MyTable(QWidget* parent)
    : QTableView(/*7, 13,*/ parent)
    , m_model(new MyModel(this))
{
    setModel(m_model);

    //    QPushButton* cornerButton = reinterpret_cast<QPushButton*>(findChild<QAbstractButton*>());
    //    if (cornerButton) {
    //        cornerButton->disconnect();
    //        cornerButton->setText("123");
    //        cornerButton->setCheckable(true);
    //        //cornerButton->setEnabled(false);
    //        //connect(cornerButton, SIGNAL(clicked()), ..., ...);
    //        QCheckBox* c = new QCheckBox("№", cornerButton);
    //        c->setGeometry(cornerButton->rect() + QMargins(-5, 0, 0, 0));
    //    }

    setHorizontalHeader(new MyHeader(Qt::Horizontal, this));
    setVerticalHeader(new MyHeader(Qt::Vertical, this));

    connect(reinterpret_cast<MyHeader*>(horizontalHeader()), &MyHeader::stateChanged, m_model, &MyModel::stateChanged);
    connect(reinterpret_cast<MyHeader*>(horizontalHeader()), &MyHeader::stateChanged, [&](const QMap<int, bool>& enabled, int /*orientation*/) {
        for (int i = 0; i < enabled.size(); ++i)
            if (enabled[i])
                m_currentColumn = i;
    });
    connect(reinterpret_cast<MyHeader*>(verticalHeader()), &MyHeader::stateChanged, m_model, &MyModel::stateChanged);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    readSettings();
}

MyTable::~MyTable()
{
    writeSettings();
}

void MyTable::showEvent(QShowEvent* /*event*/)
{
    resizeEvent(0);
    resizeRowsToContents();
}

QMap<int, bool> MyTable::IsChecked()
{
    return m_model->rowsEnabled();
}

void MyTable::AddData(int num, double val)
{
    m_model->setChData(m_model->getChData(num, m_currentColumn) * 0.9 + val * 0.1, num, m_currentColumn);
}

void MyTable::ClearColumnData()
{
    for (int var = 0; var < 58; ++var)
        m_model->setChData(0.0, var, m_currentColumn);
}

void MyTable::ClearRowData(int num)
{
    m_model->setChData(0.0, num, m_currentColumn);
}

void MyTable::SetData(int num, double val)
{
    m_model->setChData(val, num, m_currentColumn);
}

void MyTable::SetEnabledCheckBoxes(bool flag)
{
    horizontalHeader()->setEnabled(flag);
    verticalHeader()->setEnabled(flag);
}

void MyTable::writeSettings()
{
    QSettings settings;
    settings.beginGroup("TableCoefficients");
    settings.setValue("lastPath", m_lastPath);
    settings.endGroup();
}

void MyTable::readSettings()
{
    QSettings settings;
    settings.beginGroup("TableCoefficients");
    m_lastPath = settings.value("lastPath").toString();
    settings.endGroup();
}

void MyTable::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu;
    QAction* at = menu.addAction(QIcon(), "Копировать данные", [&]() {
        QClipboard* m_clipboard{ QApplication ::clipboard() };
        QString str;
        const int columnCount = model()->columnCount();
        for (int col = 0; col < columnCount; ++col) {
            str.append(m_model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString() + '\t');
        }
        str.append("\r\n");
        for (int row = 0; row < 58; ++row) {
            for (int col = 0; col < columnCount; ++col) {
                str.append(QString::number(m_model->getChData(row, col)) + '\t');
            }
            str.append("\r\n");
        }
        m_clipboard->setText(str.replace('.', ','));
    },
        QKeySequence(QKeySequence::Copy));
    menu.exec(event->globalPos(), at);
}

//////////////////////////////////////////////////////////////
/// \brief MyHeader::MyHeader
/// \param orientation
/// \param parent
///
MyHeader::MyHeader(Qt::Orientation orientation, QWidget* parent)
    : QHeaderView(orientation, parent)
{
    QSettings settings;
    int size = settings.beginReadArray("MyHeader" + QString::number(orientation));
    for (int i = 0, key = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        key = settings.value("key").toInt();
        if (key > -1)
            m_isOn[key] = settings.value("value").toBool();
    }
    settings.endArray();
    //Отправить сигнал после установки всех соединений.
    QTimer::singleShot(1, Qt::CoarseTimer, [=] { emit stateChanged(m_isOn, orientation); });
}

MyHeader::~MyHeader()
{
    QSettings settings;
    settings.beginWriteArray("MyHeader" + QString::number(orientation()));
    int j = 0;
    QMap<int, bool>::const_iterator i = m_isOn.constBegin();
    while (i != m_isOn.constEnd()) {
        settings.setArrayIndex(j++);
        settings.setValue("key", i.key());
        settings.setValue("value", i.value());
        ++i;
    }
    settings.endArray();
}

void MyHeader::mouseMoveEvent(QMouseEvent* event)
{
    if (orientation() == Qt::Horizontal)
        return;
    static int index = 0;
    if (index != logicalIndexAt(event->pos())) {
        index = logicalIndexAt(event->pos());
        if (event->buttons() & Qt::LeftButton) {
            m_isOn[index] = !m_isOn[index];
            updateSection(index);
            stateChanged(m_isOn, orientation());
        }
    }
}

void MyHeader::mousePressEvent(QMouseEvent* event)
{
    int index = logicalIndexAt(event->pos());
    if (orientation() == Qt::Horizontal) {
        for (int var = 0; var < count(); ++var)
            m_isOn[var] = false;
        m_isOn[index] = true;
        for (int var = 0; var < count(); ++var)
            updateSection(var);
    } else {
        m_isOn[index] = !m_isOn[index];
        updateSection(index);
    }

    stateChanged(m_isOn, orientation());

    QHeaderView::mousePressEvent(event);
}

void MyHeader::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    QStyleOptionButton option;
    option.rect = QRect(rect.left() + 4, (rect.height() - 16) / 2 + rect.top(), 16, 16);

    m_isOn[logicalIndex] ? option.state = QStyle::State_On : option.state = QStyle::State_Off;
    option.state |= (isEnabled() ? QStyle::State_Enabled : QStyle::State_None);
    if (orientation() == Qt::Horizontal)
        style()->drawPrimitive(QStyle::PE_IndicatorRadioButton, &option, painter);
    else
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
}
