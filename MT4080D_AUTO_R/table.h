#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>

class Table : public QWidget {
    Q_OBJECT
public:
    explicit Table(QWidget* parent = 0);
    ~Table();

    bool IsChecked(int row)
    {
        return (m_tableData->item(row, 0)->checkState() == Qt::Checked);
    }
    void AddData(int num, double val)
    {
        if (num >= 58) {
            return;
        }
        double average = 0.0;
        int i;
        m_data[num][m_currentColumn].append(val);
        for (i = 0; i < m_data[num][m_currentColumn].size(); ++i) {
            average += m_data[num][m_currentColumn][i];
        }
        m_tableData->item(num, m_currentColumn + 1)->setText(QString("%1").arg(average / i).replace('.', ','));
        m_tableData->scrollToItem(m_tableData->item(num, m_currentColumn + 1));
    }
    void ClearColumnData()
    {
        if (QMessageBox::question(this, "Вопрос", "Вы действительно хотите отчистить столбец?!", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            for (int i = 0; i < 58; ++i) {
                m_data[i][m_currentColumn].clear();
                m_data[i][m_currentColumn].append(0.0);
                m_tableData->item(i, m_currentColumn + 1)->setText(QString("%1").arg(m_data[i][m_currentColumn][0]).replace('.', ','));
                m_tableData->scrollToItem(m_tableData->item(i, m_currentColumn + 1));
            }
        }
    }
    void ClearRowData(int num)
    {
        if (num >= 58) {
            return;
        }
        m_data[num][m_currentColumn].clear();
        m_tableData->item(num, m_currentColumn + 1)->setText("");
        m_tableData->scrollToItem(m_tableData->item(num, m_currentColumn + 1));
    }
    void SetData(int num, double val)
    {
        if (num >= 58) {
            return;
        }
        m_data[num][m_currentColumn].resize(1);
        m_data[num][m_currentColumn][0] = val;
        m_tableData->item(num, m_currentColumn + 1)->setText(QString("%1").arg(val).replace('.', ','));
        m_tableData->scrollToItem(m_tableData->item(num, m_currentColumn + 1));
    }
    void SetEnabledCheckBoxes(bool flag)
    {
        for (int row = 0; row < m_tableData->rowCount(); ++row) {
            if (flag)
                m_tableData->item(row, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            else
                m_tableData->item(row, 0)->setFlags(Qt::ItemIsEnabled);
        }
        for (int col = 0; col < m_tableHeader->columnCount(); ++col) {
            if (flag)
                m_tableHeader->item(0, col)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            else
                m_tableHeader->item(0, col)->setFlags(Qt::ItemIsEnabled);
        }
    }

private:
    int m_currentColumn;
    int m_timerResizeEvent;
    QVector<double> m_data[58][4];

    QAction* m_actCopy;
    QClipboard* m_clipboard;
    QTableWidget* m_tableData;
    QTableWidget* m_tableHeader;
    QVBoxLayout* m_verticalLayout;
    QVector<int> m_flag1;

    void Copy();
    void createActions();
    void ItemClicked(QTableWidgetItem* item);
    void readSettings();
    void UpdateRowColumnEnabled();
    void writeSettings();

    // QObject interface
protected:
    void timerEvent(QTimerEvent*);

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent*);
};

#endif // TABLE_H
