#include "Diary.h"
#include "ui_Diary.h"
#include <QTextStream>
#include <QFont>
#include <QUrl>

Diary::Diary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Diary)
{
    ui->setupUi(this);
    setWindowIcon(QIcon (":/res/res/icon.png"));
    setWindowTitle("今天写乐日记");
    getDiary();
}

Diary::~Diary()
{
    delete ui;
}


void Diary::on_actionadd_triggered()
{
    Diary_text *text = new Diary_text;
    text->setAttribute(Qt::WA_DeleteOnClose);
    text->show();
}

void Diary::onFileSelected()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
            if (index.isValid() && fileModel->fileInfo(index).isFile() &&
                fileModel->fileInfo(index).suffix() == "txt") {
                QString filePath = fileModel->fileInfo(index).absoluteFilePath();
                QFile file(filePath);
                if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&file);
                    QString content = in.readAll();
                    ui->textBrowser->setText(content); // 或者使用 setPlainText() 显示纯文本
                    file.close();
                }
            } else {
                ui->textBrowser->clear(); // 如果没有选中txt文件，则清空文本浏览器
            }
}

void Diary::getDiary()
{
    // 创建文件系统模型
    fileSystemModel = new QFileSystemModel(this);

    // 设置根目录为你想要显示的文件夹
    QString rootPath = "Diary"; // 替换为你的文件夹路径
    fileSystemModel->setRootPath(rootPath);

    // 设置QTreeView的模型
    ui->treeView->setModel(fileSystemModel);

    // 设置QTreeView的根索引为想要显示的文件夹的索引
    ui->treeView->setRootIndex(fileSystemModel->index(rootPath));

    // 隐藏列，只显示名称列
    ui->treeView->setColumnHidden(1, true); // 隐藏大小列
    ui->treeView->setColumnHidden(2, true); // 隐藏日期列
    ui->treeView->setColumnHidden(3, true); // 隐藏类型列（文件/文件夹）

    // 可选：设置QTreeView的标题不可见
    ui->treeView->setHeaderHidden(true);

    // 连接信号和槽控制日记显示
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &Diary::onFileSelected);
}
