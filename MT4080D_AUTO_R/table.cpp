#include "table.h"

Q_DECLARE_METATYPE(Qt::CheckState)

Table::Table(QWidget* parent)
    : QWidget(parent)
    , m_flag1(QVector<int>(10, Qt::Unchecked))
    , m_clipboard(QApplication::clipboard())
{
    qRegisterMetaTypeStreamOperators<QVector<int> >("QVector<int>");
    qRegisterMetaTypeStreamOperators<QVector<double> >("QVector<double>");

    //memset(m_data, 0, sizeof(double) * 58 * 4 * 100);
    for (int i = 0; i < 58; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j].clear();
            m_data[i][j].append(0.0);
        }
    }

    m_verticalLayout = new QVBoxLayout(this);
    m_verticalLayout->setSpacing(0);
    m_verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    m_verticalLayout->setContentsMargins(0, 0, 0, 0);
    m_tableHeader = new QTableWidget(1, 5, this);
    m_tableHeader->setObjectName(QStringLiteral("tabletHeader"));
    m_tableHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_verticalLayout->addWidget(m_tableHeader);
    m_tableData = new QTableWidget(58, 5, this);
    m_tableData->setObjectName(QStringLiteral("tableData"));
    m_tableData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_verticalLayout->addWidget(m_tableData);

    QStringList list;
    list << "№"
         << "Измерение\r\n1"
         << "Измерение\r\n2"
         << "Измерение\r\n3"
         << "Измерение\r\n4";

    m_tableData->setHorizontalHeaderLabels(list);
    m_tableData->verticalHeader()->setVisible(false);
    m_tableData->horizontalHeader()->setVisible(false);

    for (int row = 0; row < m_tableData->rowCount(); ++row) {
        for (int col = 0; col < m_tableData->columnCount(); ++col) {
            QTableWidgetItem* tableitem = new QTableWidgetItem("QTableWidgetItem");
            tableitem->setFlags(Qt::ItemIsEnabled);
            tableitem->setToolTip(QString("R%1, C%2").arg(row + 1).arg(col));
            if (col == 0) {
                tableitem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
                tableitem->setCheckState(Qt::Checked);
                tableitem->setText(QString("%1").arg(row + 1));
                tableitem->setToolTip(QString("Позиция элемента на тестовой плате.\r\nВ данном случае %1").arg(row + 1));
            }
            tableitem->setTextAlignment(Qt::AlignCenter);
            m_tableData->setItem(row, col, tableitem);
        }
    }
    m_tableHeader->verticalHeader()->setVisible(false);
    m_tableHeader->horizontalHeader()->setVisible(false);
    m_tableHeader->setHorizontalHeaderLabels(list);
    for (int col = 0; col < m_tableHeader->columnCount(); ++col) {
        QTableWidgetItem* tableitem = new QTableWidgetItem("QTableWidgetItem");
        tableitem->setTextAlignment(Qt::AlignCenter);
        tableitem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        tableitem->setCheckState(Qt::Checked);

        tableitem->setText(list[col]);
        tableitem->setToolTip(list[col]);
        m_tableHeader->setItem(0, col, tableitem);
    }
    connect(m_tableData, &QTableWidget::itemClicked, this, &Table::ItemClicked);
    connect(m_tableHeader, &QTableWidget::itemClicked, this, &Table::ItemClicked);

    readSettings();
    createActions();

    m_timerResizeEvent = startTimer(100);
}

Table::~Table()
{
    writeSettings();
}









void Table::writeSettings()
{
    QSettings settings;
    settings.beginGroup("TABLE");

    settings.setValue("flag1", QVariant::fromValue(m_flag1));

    m_flag1.clear();
    for (int col = 0; col < m_tableHeader->columnCount(); ++col) {
        m_flag1.push_back(m_tableHeader->item(0, col)->checkState());
    }
    settings.setValue("checkStateCol", QVariant::fromValue(m_flag1));

    m_flag1.clear();
    for (int row = 0; row < m_tableData->rowCount(); ++row) {
        m_flag1.push_back(m_tableData->item(row, 0)->checkState());
    }
    settings.setValue("checkStateRow", QVariant::fromValue(m_flag1));

    settings.endGroup();

    QSettings data("Data.txt", QSettings::IniFormat);
    data.beginGroup("data");
    for (int i = 0; i < 58; ++i) {
        for (int j = 0; j < 4; ++j) {
            data.setValue(QString("%1_%2").arg(i).arg(j), QVariant::fromValue(m_data[i][j]));
            //            qDebug() << i << j << m_data[i][j];
        }
    }
    data.endGroup();
    //    QFile file("Data.txt");
    //    if (!file.open(QIODevice::WriteOnly))
    //        return;
    //    file.write((char*)m_data, sizeof(double) * 58 * 4 * 100);
}

void Table::readSettings()
{
    QSettings settings;
    settings.beginGroup("TABLE");

    m_flag1 = settings.value("checkStateCol").value<QVector<int> >();
    for (int col = 0; col < m_tableHeader->columnCount() && col < m_flag1.size(); ++col) {
        m_tableHeader->item(0, col)->setCheckState(Qt::CheckState(m_flag1[col]));
        if (Qt::Checked == m_flag1[col] && col) {
            m_currentColumn = col - 1;
        }
    }

    m_flag1 = settings.value("checkStateRow").value<QVector<int> >();
    for (int row = 0; row < m_tableData->rowCount() && row < m_flag1.size(); ++row) {
        m_tableData->item(row, 0)->setCheckState(Qt::CheckState(m_flag1[row]));
    }

    m_flag1 = settings.value("flag1").value<QVector<int> >();
    if (m_flag1.size() < m_tableHeader->columnCount()) {
        m_flag1.resize(m_tableHeader->columnCount());
    }

    ItemClicked(m_tableData->item(0, 0));

    settings.endGroup();

    QSettings data("Data.txt", QSettings::IniFormat);
    data.beginGroup("data");
    QVector<double> tmp;
    tmp.append(0.0);
    for (int i = 0; i < 58; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j] = data.value(QString("%1_%2").arg(i).arg(j), QVariant::fromValue(tmp)).value<QVector<double> >();
        }
    }
    data.endGroup();
    //    QFile file("Data.txt");
    //    if (!file.open(QIODevice::ReadOnly))
    //        return;
    //    if (file.size() >= (sizeof(double) * 58 * 4 * 100))
    //        file.read((char*)m_data, sizeof(double) * 58 * 4 * 100);

    for (int row = 0; row < m_tableData->rowCount(); ++row) {
        for (int col = 1; col < m_tableData->columnCount(); ++col) {
            double average;
            average = 0.0;
            int i;
            for (i = 0; i < m_data[row][col - 1].size(); ++i) {
                average += m_data[row][col - 1][i];
            }
            m_tableData->item(row, col)->setText(QString("%1").arg(average / i).replace('.', ','));
        }
    }
}

void Table::createActions()
{
    m_actCopy = new QAction(tr("Копировать данные"), this);
    connect(m_actCopy, &QAction::triggered, this, &Table::Copy);
}

void Table::UpdateRowColumnEnabled()
{
    for (int row = 0; row < m_tableData->rowCount(); ++row) {
        for (int col = 1; col < m_tableData->columnCount(); ++col) {
            if (m_tableData->item(row, 0)->checkState() == Qt::Checked && m_tableHeader->item(0, col)->checkState() == Qt::Checked) {
                m_tableData->item(row, col)->setFlags(Qt::ItemIsEnabled);
            }
            else {
                m_tableData->item(row, col)->setFlags(Qt::NoItemFlags);
            }
        }
    }
}

void Table::Copy()
{
    QString str;
    for (int col = 0; col < m_tableHeader->columnCount(); ++col) {
        str.append(m_tableHeader->item(0, col)->text().replace("\r\n", " ") + '\t');
    }
    str.append("\r\n");
    for (int row = 0; row < m_tableData->rowCount(); ++row) {
        for (int col = 0; col < m_tableData->columnCount(); ++col) {
            str.append(m_tableData->item(row, col)->text() + '\t');
        }
        str.append("\r\n");
    }
    m_clipboard->setText(str);
}

void Table::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    menu.addAction(m_actCopy);
    menu.exec(event->globalPos());
}





void Table::ItemClicked(QTableWidgetItem* item)
{
    if (!item)
        return;

    if (item->flags().testFlag(Qt::ItemIsUserCheckable)) {
        if (item->tableWidget() == m_tableData) {
            if (item->column() == 0) {
                for (int col = 1; col < 5; ++col) {
                    m_tableData->item(item->row(), col)->setFlags(item->checkState() == Qt::Checked ? Qt::ItemIsEnabled : Qt::NoItemFlags);
                }
            }
        }
        if (item->tableWidget() == m_tableHeader) {
            int column = item->column();
            if (column == 0) {
                for (int row = 0; row < m_tableData->rowCount(); ++row) {
                    m_tableData->item(row, 0)->setCheckState(item->checkState());
                }
            }
            else {
                if (m_currentColumn != column - 1) {
                    m_currentColumn = column - 1;
                    for (int col = 1; col < m_tableHeader->columnCount(); ++col) {
                        if (col != column) {
                            m_tableHeader->item(0, col)->setCheckState(Qt::Unchecked);
                            m_flag1[column] = Qt::Unchecked;
                        }
                    }
                    item->setCheckState(Qt::Checked);
                }
                else {
                    item->setCheckState(Qt::Checked);
                }
            }
        }
        UpdateRowColumnEnabled();
    }
}

void Table::timerEvent(QTimerEvent* e)
{
    static QSize Size;
    if (e->timerId() == m_timerResizeEvent) {
        if (Size.width() != m_tableData->size().width()) {
            Size = size();
            m_tableData->resizeColumnsToContents();
            m_tableData->resizeRowsToContents();
            int ColumnWidth = size().width()
                - 2
                - (m_tableData->columnWidth(0))
                - (m_tableData->verticalScrollBar()->isVisible() ? m_tableData->verticalScrollBar()->width() : 0);
            int ColumnWidth2 = ColumnWidth / 4;
            m_tableData->setColumnWidth(1, ColumnWidth2);
            m_tableData->setColumnWidth(2, ColumnWidth2);
            m_tableData->setColumnWidth(3, ColumnWidth2);
            m_tableData->setColumnWidth(4, ColumnWidth - (ColumnWidth2 * 3));
            if (m_tableHeader) {
                m_tableHeader->resizeRowsToContents();
                for (int col = 0; col < m_tableData->columnCount(); ++col) {
                    m_tableHeader->setColumnWidth(col, m_tableData->columnWidth(col));
                }
                m_tableHeader->setMaximumHeight(m_tableHeader->rowHeight(0));
            }
        }
    }
}
