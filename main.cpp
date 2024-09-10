#include <QApplication>
#include <QFile>
#include <QDebug>
#include "AppLauncher.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Load and apply the stylesheet
    QFile file("C:/Users/Kliea/Documents/Development/Liadrin/Styles/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString stylesheet = QLatin1String(file.readAll());
        a.setStyleSheet(stylesheet);
        file.close();
    } else {
        qDebug() << "Could not open stylesheet file.";
    }

    AppLauncher w;
    w.show();

    return a.exec();
}





// #include <QApplication>
// #include "AppLauncher.h"

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     // Set global stylesheet
//     app.setStyleSheet(
//         "QMainWindow { background-color: #2c3e50; }"
//         "QListWidget { background-color: #34495e; color: white; }"
//         "QListWidget::item { padding: 10px; }"
//         "QScrollArea { background-color: #ecf0f1; border: none; }"
//         "QLabel { color: #ecf0f1; font-size: 14px; font-weight: bold; }"
//         "ClickableWidget { border: 1px solid #2980b9; border-radius: 10px; background-color: #3498db; }"
//         "ClickableWidget:hover { background-color: #1abc9c; }"
//         );

//     AppLauncher launcher;
//     launcher.show();
//     return app.exec();
// }



// #include <QApplication>
// #include "AppLauncher.h"

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     AppLauncher launcher;
//     launcher.show();

//     return app.exec();
// }
