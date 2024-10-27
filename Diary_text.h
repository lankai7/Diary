#ifndef DIARY_TEXT_H
#define DIARY_TEXT_H

#include <QWidget>

namespace Ui {
class Diary_text;
}

class Diary_text : public QWidget
{
    Q_OBJECT

public:
    explicit Diary_text(QWidget *parent = nullptr);
    ~Diary_text();

private slots:
    void on_Btn_save_clicked();

private:
    Ui::Diary_text *ui;
    //日期时间
    int year;
    int month;
    int day;
    //文件位置名称
    QString SpaceName;
    QString fileName;
    //title
    QString title;

    void getTime();
    void creatFile();
    void isfile();
};

#endif // DIARY_TEXT_H
