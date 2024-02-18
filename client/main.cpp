#include <QApplication>
#include <QFile>
#include <QDir>


#include <QDebug>

namespace client { void show(); }

static void applyDarkTheme()
{
    QFile file(":/theme/resources/themes/dark.qss");
    if (file.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());
    
    applyDarkTheme();
    
    client::show();
    
    return a.exec();
}
