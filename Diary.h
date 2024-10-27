#ifndef DIARY_H
#define DIARY_H

#include <QMainWindow>
#include "Diary_text.h"
#include <QFileSystemModel>
#include <QItemSelection>

QT_BEGIN_NAMESPACE
namespace Ui { class Diary; }
QT_END_NAMESPACE

class Diary : public QMainWindow
{
    Q_OBJECT

public:
    Diary(QWidget *parent = nullptr);
    ~Diary();

private slots:
    void on_actionadd_triggered();
    void onFileSelected();

private:
    Ui::Diary *ui;
    QFileSystemModel *fileSystemModel;
    QFileSystemModel *fileModel;
    void getDiary();
};
#endif // DIARY_H
