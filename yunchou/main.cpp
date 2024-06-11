#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

// 主函数
int main(int argc, char *argv[])
{
    // 创建一个QApplication对象
    QApplication a(argc, argv);

    // 创建一个QTranslator对象，用于加载翻译文件
    QTranslator translator;
    // 获取系统的UI语言列表
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    // 遍历系统UI语言列表，尝试加载对应的翻译文件
    for (const QString &locale : uiLanguages) {
        const QString baseName = "yunchou_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            // 如果成功加载翻译文件，将其安装到应用程序中
            a.installTranslator(&translator);
            break;
        }
    }
    // 创建并显示主窗口
    MainWindow w;
    w.show();
    // 输出调试信息
    qDebug() << "1234" << endl;
    // 进入应用程序的事件循环
    return a.exec();
}
