#include "Diary_text.h"
#include "ui_Diary_text.h"
#include <QDebug>
#include <QDir>

#include <iostream>

Diary_text::Diary_text(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diary_text)
{
    ui->setupUi(this);
    setWindowIcon(QIcon (":/res/res/icon.png"));
    getTime();
    creatFile();
    isfile();
}

Diary_text::~Diary_text()
{
    delete ui;
}

void Diary_text::on_Btn_save_clicked()
{
    // 打开文件进行写操作
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing:" << file.errorString();
        return;
    }

    // 获取日记文本
    QString diaryText = ui->plainTextEdit->toPlainText();

    // 写入文件
    QTextStream out(&file);
    out << diaryText << "\n";

    // 关闭文件
    qDebug() <<"Writing successful:"<<fileName;
    file.close();
}

void Diary_text::getTime()
{
    std::time_t now = std::time(nullptr);

    // 转换为本地时间
    std::tm* localTime = std::localtime(&now);
    // 获取年、月、日
    year = localTime->tm_year + 1900;
    month = localTime->tm_mon + 1;
    day = localTime->tm_mday;

    title = QString::number(year) + "年" + QString::number(month) + "月" + QString::number(day) +"日";
    setWindowTitle(title);
}

void Diary_text::creatFile()
{
    // 构建文件名
    SpaceName = "Diary\\" + QString("%1年\\%2月").arg(year).arg(month);
    fileName = SpaceName + "\\" + QString::number(day)+"日.txt";
    qDebug() << "SpaceName:" << SpaceName;

    // 创建QDir对象
    QDir dir;

    // 检查名为SpaceName的文件夹是否存在
    if (!dir.exists(SpaceName)) {
        // 如果不存在，尝试在当前工作目录下创建它
        if (!dir.mkpath(SpaceName)) {
            // 创建失败
            qDebug() << "Failed to create folder:" << SpaceName;
        } else {
            // 创建成功
            qDebug() << "Folder created successfully:" << SpaceName;
        }
    } else {
        // 文件夹已经存在
        qDebug() << "Folder already exists:" << SpaceName;
    }
}

void Diary_text::isfile()
{
    // 创建QFile对象
    QFile file(fileName);
    // 检查文件是否存在
    if (file.exists()) {
        // 打开文件以只读方式
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // 创建QTextStream对象以读取文件内容
            QTextStream in(&file);
            QString content = in.readAll(); // 读取整个文件内容

            // 打印文件内容
            ui->plainTextEdit->appendPlainText(content);

            // 关闭文件
            file.close();
        } else {
            qDebug() << "Failed to open file:" << fileName;
        }
    } else {
        ui->plainTextEdit->appendPlainText(title + "\n\n");
        qDebug() << "File does not exist:" << fileName;
    }
}
