#ifndef TABLE_COEFFICIENTS_H
#define TABLE_COEFFICIENTS_H

#include <QDate>
#include <QHeaderView>
#include <QTableView>

class MyHeader : public QHeaderView {
    Q_OBJECT
public:
    MyHeader(Qt::Orientation orientation, QWidget* parent = 0);
    ~MyHeader();
    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;

signals:
    void stateChanged(const QMap<int, bool>&, int);

private:
    QMap<int, bool> m_isOn;
};

class MyModel;

class MyTable : public QTableView {
    Q_OBJECT
public:
    explicit MyTable(QWidget* parent = 0);
    ~MyTable();

    QMap<int, bool> IsChecked();
    void AddData(int num, double val);
    void ClearColumnData();
    void ClearRowData(int num);
    void SetData(int num, double val);
    void SetEnabledCheckBoxes(bool flag);

signals:
    void dateChanged(const QDate& date);
    void FileName(const QString& date);

private:
    QString m_lastPath;

    void writeSettings();
    void readSettings();
    MyModel* m_model;
    int m_currentColumn = 0;

    // QWidget interface
protected:
    void showEvent(QShowEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLE_COEFFICIENTS_H
