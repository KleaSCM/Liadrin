#include "AppLauncher.h"
#include "ui_AppLauncher.h"
#include "ClickableWidget.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QProcess>
#include <QMessageBox>

AppLauncher::AppLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppLauncher),
    appGridLayout(new QGridLayout)
{
    ui->setupUi(this);

    // Set up the central widget and layout
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Create and configure the category list
    QListWidget *categoryList = new QListWidget;
    mainLayout->addWidget(categoryList);
    ui->categoryList = categoryList;

    // Create and configure the scroll area for apps
    QWidget *appContainerWidget = new QWidget;
    appContainerWidget->setLayout(appGridLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(appContainerWidget);
    mainLayout->addWidget(scrollArea);

    connect(ui->categoryList, &QListWidget::currentTextChanged, this, &AppLauncher::onCategoryChanged);
    connect(ui->searchButton, &QPushButton::clicked, this, &AppLauncher::onSearch);

    populateCategories();
}

AppLauncher::~AppLauncher() {
    delete ui;
    delete appGridLayout;
}

void AppLauncher::onCategoryChanged() {
    QString selectedCategory = ui->categoryList->currentItem()->text();
    populateApps(selectedCategory);
}

void AppLauncher::onSearch() {
    // Implement search functionality
}

void AppLauncher::onAppClicked(const QString &appPath) {
    if (!QProcess::startDetached(appPath)) {
        QMessageBox::warning(this, "Launch Failed", "Could not launch application.");
    }
}

void AppLauncher::populateCategories() {
    QStringList categories = {"Games", "Development", "Office", "Web", "Tools"};
    ui->categoryList->addItems(categories);
}

void AppLauncher::populateApps(const QString &category) {
    QLayoutItem *item;
    while ((item = appGridLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    if (category == "Games") {
        addAppCard("Diablo IV", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/diablo_iv.png", "C:/Program Files (x86)/Diablo IV/Diablo IV.exe");
        addAppCard("Path of Exile", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/PathOfExile.png", "C:/Program Files (x86)/Steam/steamapps/common/Path of Exile/PathOfExile_x64Steam.exe");
        addAppCard("World of Warcraft", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/WoW.png", "C:/Program Files (x86)/World of Warcraft/World of Warcraft Launcher.exe");
        addAppCard("Battle.net", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Battle.net.jpg", "C:/Program Files (x86)/Battle.net/Battle.net Launcher.exe");
    } else if (category == "Development") {
        addAppCard("Awakened PoE Trade", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/share.jpg", "C:/Users/Kliea/Documents/Development/Axolotl/Axolotl/front/axolotl/public/utils/paths/Awakened PoE Trade.exe.lnk");
        addAppCard("Python", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/code.jpg", "C:/Python312/python.exe");
        addAppCard("NVIDIA GeForce Experience", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/NVIDIA GeForce Experience.jpg", "C:/Program Files/NVIDIA Corporation/NVIDIA GeForce Experience/NVIDIA GeForce Experience.exe");
    } else if (category == "Office") {
        addAppCard("Excel", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Excel.png", "C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE");
        addAppCard("PowerPoint", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Powerpoint.jpg", "C:/Program Files/Microsoft Office/root/Office16/POWERPNT.EXE");
        addAppCard("Word", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/WINWORD.jpg", "C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE");
        addAppCard("Microsoft Teams", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Teams.jpg", "C:/Users/Kliea/AppData/Local/Microsoft/Teams/Update.exe --processStart \"Teams.exe\"");
    } else if (category == "Web") {
        addAppCard("Steam", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Steam.jpg", "C:/Program Files (x86)/Steam/steam.exe");
        addAppCard("Vivaldi", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/code.jpg", "C:/Users/Kliea/AppData/Local/Vivaldi/Application/vivaldi.exe");
    } else if (category == "Tools") {
        addAppCard("PowerShell", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/Windows PowerShell.jpg", "%SystemRoot%/system32/WindowsPowerShell/v1.0/powershell.exe");
        addAppCard("Visual Studio Installer", "C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/vs.jpg", "C:/Program Files (x86)/Microsoft Visual Studio/Installer/setup.exe");
    }
}

void AppLauncher::addAppCard(const QString &appName, const QString &iconPath, const QString &appPath) {
    ClickableWidget *cardWidget = new ClickableWidget;
    QVBoxLayout *cardLayout = new QVBoxLayout(cardWidget);

    QLabel *iconLabel = new QLabel;
    if (QPixmap(iconPath).isNull()) {
        iconLabel->setPixmap(QPixmap("C:/Users/Kliea/Documents/Development/Liadrin/resources/icons/placeholder.png").scaled(64, 64, Qt::KeepAspectRatio));
    } else {
        iconLabel->setPixmap(QPixmap(iconPath).scaled(64, 64, Qt::KeepAspectRatio));
    }

    QLabel *nameLabel = new QLabel(appName);

    cardLayout->addWidget(iconLabel);
    cardLayout->addWidget(nameLabel);
    cardWidget->setLayout(cardLayout);

    int row = appGridLayout->count() / 5;
    int col = appGridLayout->count() % 5;
    appGridLayout->addWidget(cardWidget, row, col);

    connect(cardWidget, &ClickableWidget::clicked, [this, appPath]() {
        onAppClicked(appPath);
    });
}







































































// #include "AppLauncher.h"
// #include "ui_AppLauncher.h"
// #include "ClickableWidget.h"

// #include <QVBoxLayout>
// #include <QPixmap>
// #include <QProcess>
// #include <QMessageBox>

// AppLauncher::AppLauncher(QWidget *parent) :
//     QMainWindow(parent),
//     ui(new Ui::AppLauncher),
//     appGridLayout(new QGridLayout)
// {
//     ui->setupUi(this);

//     // Set up the central widget and layout
//     QWidget *centralWidget = new QWidget;
//     setCentralWidget(centralWidget);
//     QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//     // Create and configure the category list
//     QListWidget *categoryList = new QListWidget;
//     mainLayout->addWidget(categoryList);
//     ui->categoryList = categoryList;

//     // Create and configure the scroll area for apps
//     QWidget *appContainerWidget = new QWidget;
//     appContainerWidget->setLayout(appGridLayout);
//     QScrollArea *scrollArea = new QScrollArea;
//     scrollArea->setWidgetResizable(true);
//     scrollArea->setWidget(appContainerWidget);
//     mainLayout->addWidget(scrollArea);

//     connect(ui->categoryList, &QListWidget::currentTextChanged, this, &AppLauncher::onCategoryChanged);
//     connect(ui->searchButton, &QPushButton::clicked, this, &AppLauncher::onSearch);

//     populateCategories();
// }

// AppLauncher::~AppLauncher() {
//     delete ui;
//     delete appGridLayout;
// }

// void AppLauncher::onCategoryChanged() {
//     QString selectedCategory = ui->categoryList->currentItem()->text();
//     populateApps(selectedCategory);
// }

// void AppLauncher::onSearch() {
//     // Implement search functionality
// }

// void AppLauncher::onAppClicked(const QString &appPath) {
//     if (!QProcess::startDetached(appPath)) {
//         QMessageBox::warning(this, "Launch Failed", "Could not launch application.");
//     }
// }

// void AppLauncher::populateCategories() {
//     QStringList categories = {"Games", "Development", "Office", "Web", "Tools"};
//     ui->categoryList->addItems(categories);
// }

// void AppLauncher::populateApps(const QString &category) {
//     QLayoutItem *item;
//     while ((item = appGridLayout->takeAt(0))) {
//         delete item->widget();
//         delete item;
//     }

//     if (category == "Games") {
//         addAppCard("Diablo IV", ":/icons/diablo_iv.png", "C:/Program Files (x86)/Diablo IV/Diablo IV.exe");
//         addAppCard("Path of Exile", ":/icons/poe.png", "C:/Program Files (x86)/Steam/steamapps/common/Path of Exile/PathOfExile_x64Steam.exe");
//         addAppCard("World of Warcraft", ":/icons/wow.png", "C:/Program Files (x86)/World of Warcraft/World of Warcraft Launcher.exe");
//         addAppCard("Battle.net", ":/icons/battlenet.png", "C:/Program Files (x86)/Battle.net/Battle.net Launcher.exe");
//     } else if (category == "Development") {
//         addAppCard("Awakened PoE Trade", ":/icons/awakened_poe_trade.png", "C:/Users/Kliea/Documents/Development/Axolotl/Axolotl/front/axolotl/public/utils/paths/Awakened PoE Trade.exe.lnk");
//         addAppCard("Python", ":/icons/python.png", "C:/Python312/python.exe");
//         addAppCard("NVIDIA GeForce Experience", ":/icons/nvidia.png", "C:/Program Files/NVIDIA Corporation/NVIDIA GeForce Experience/NVIDIA GeForce Experience.exe");
//     } else if (category == "Office") {
//         addAppCard("Excel", ":/icons/excel.png", "C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE");
//         addAppCard("PowerPoint", ":/icons/powerpoint.png", "C:/Program Files/Microsoft Office/root/Office16/POWERPNT.EXE");
//         addAppCard("Word", ":/icons/word.png", "C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE");
//         addAppCard("Microsoft Teams", ":/icons/teams.png", "C:/Users/Kliea/AppData/Local/Microsoft/Teams/Update.exe --processStart \"Teams.exe\"");
//     } else if (category == "Web") {
//         addAppCard("Steam", ":/icons/steam.png", "C:/Program Files (x86)/Steam/steam.exe");
//         addAppCard("Vivaldi", ":/icons/vivaldi.png", "C:/Users/Kliea/AppData/Local/Vivaldi/Application/vivaldi.exe");
//     } else if (category == "Tools") {
//         addAppCard("PowerShell", ":/icons/powershell.png", "%SystemRoot%/system32/WindowsPowerShell/v1.0/powershell.exe");
//         addAppCard("Visual Studio Installer", ":/icons/visual_studio.png", "C:/Program Files (x86)/Microsoft Visual Studio/Installer/setup.exe");
//     }
// }

// void AppLauncher::addAppCard(const QString &appName, const QString &iconPath, const QString &appPath) {
//     ClickableWidget *cardWidget = new ClickableWidget;
//     QVBoxLayout *cardLayout = new QVBoxLayout(cardWidget);

//     QLabel *iconLabel = new QLabel;
//     iconLabel->setPixmap(QPixmap(iconPath).scaled(64, 64, Qt::KeepAspectRatio));
//     QLabel *nameLabel = new QLabel(appName);

//     cardLayout->addWidget(iconLabel);
//     cardLayout->addWidget(nameLabel);
//     cardWidget->setLayout(cardLayout);

//     int row = appGridLayout->count() / 5;
//     int col = appGridLayout->count() % 5;
//     appGridLayout->addWidget(cardWidget, row, col);

//     connect(cardWidget, &ClickableWidget::clicked, [this, appPath]() {
//         onAppClicked(appPath);
//     });
// }


// #include "AppLauncher.h"
// #include "ui_AppLauncher.h"
// #include "ClickableWidget.h"

// #include <QVBoxLayout>
// #include <QPixmap>
// #include <QProcess> // For launching applications
// #include <QMessageBox>

// AppLauncher::AppLauncher(QWidget *parent) :
//     QMainWindow(parent),
//     ui(new Ui::AppLauncher),
//     appGridLayout(new QGridLayout)
// {
//     ui->setupUi(this);

//     // Set up the central widget and layout
//     QWidget *centralWidget = new QWidget;
//     setCentralWidget(centralWidget);
//     QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//     // Create and configure the category list
//     QListWidget *categoryList = new QListWidget;
//     mainLayout->addWidget(categoryList);
//     ui->categoryList = categoryList;

//     // Create and configure the scroll area for apps
//     QWidget *appContainerWidget = new QWidget;
//     appContainerWidget->setLayout(appGridLayout);
//     QScrollArea *scrollArea = new QScrollArea;
//     scrollArea->setWidgetResizable(true);
//     scrollArea->setWidget(appContainerWidget);
//     mainLayout->addWidget(scrollArea);

//     connect(ui->categoryList, &QListWidget::currentTextChanged, this, &AppLauncher::onCategoryChanged);
//     connect(ui->searchButton, &QPushButton::clicked, this, &AppLauncher::onSearch);

//     populateCategories(); // Ensure categories are populated on initialization
// }

// AppLauncher::~AppLauncher() {
//     delete ui;
//     delete appGridLayout;
// }

// void AppLauncher::onCategoryChanged() {
//     QString selectedCategory = ui->categoryList->currentItem()->text();
//     populateApps(selectedCategory);
// }

// void AppLauncher::onSearch() {
//     // Implement search functionality
// }

// void AppLauncher::onAppClicked(const QString &appPath) {
//     if (!QProcess::startDetached(appPath)) {
//         QMessageBox::warning(this, "Launch Failed", "Could not launch application.");
//     }
// }

// void AppLauncher::populateCategories() {
//     QStringList categories = {"Games", "Development", "Office", "Web", "Tools"};
//     ui->categoryList->addItems(categories);
// }

// void AppLauncher::populateApps(const QString &category) {
//     QLayoutItem *item;
//     while ((item = appGridLayout->takeAt(0))) {
//         delete item->widget();
//         delete item;
//     }

//     if (category == "Games") {
//         addAppCard("Diablo IV", ":/icons/diablo_iv.png", "C:/Program Files (x86)/Diablo IV/Diablo IV.exe");
//         addAppCard("Path of Exile", ":/icons/poe.png", "C:/Program Files (x86)/Steam/steamapps/common/Path of Exile/PathOfExile_x64Steam.exe");
//         addAppCard("World of Warcraft", ":/icons/wow.png", "C:/Program Files (x86)/World of Warcraft/World of Warcraft Launcher.exe");
//         addAppCard("Battle.net", ":/icons/battlenet.png", "C:/Program Files (x86)/Battle.net/Battle.net Launcher.exe");
//     } else if (category == "Development") {
//         addAppCard("Awakened PoE Trade", ":/icons/awakened_poe_trade.png", "C:/Users/Kliea/Documents/Development/Axolotl/Axolotl/front/axolotl/public/utils/paths/Awakened PoE Trade.exe.lnk");
//         addAppCard("Python", ":/icons/python.png", "C:/Python312/python.exe");
//         addAppCard("NVIDIA GeForce Experience", ":/icons/nvidia.png", "C:/Program Files/NVIDIA Corporation/NVIDIA GeForce Experience/NVIDIA GeForce Experience.exe");
//     } else if (category == "Office") {
//         addAppCard("Excel", ":/icons/excel.png", "C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE");
//         addAppCard("PowerPoint", ":/icons/powerpoint.png", "C:/Program Files/Microsoft Office/root/Office16/POWERPNT.EXE");
//         addAppCard("Word", ":/icons/word.png", "C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE");
//         addAppCard("Microsoft Teams", ":/icons/teams.png", "C:/Users/Kliea/AppData/Local/Microsoft/Teams/Update.exe --processStart \"Teams.exe\"");
//     } else if (category == "Web") {
//         addAppCard("Steam", ":/icons/steam.png", "C:/Program Files (x86)/Steam/steam.exe");
//         addAppCard("Vivaldi", ":/icons/vivaldi.png", "C:/Users/Kliea/AppData/Local/Vivaldi/Application/vivaldi.exe");
//     } else if (category == "Tools") {
//         addAppCard("PowerShell", ":/icons/powershell.png", "%SystemRoot%/system32/WindowsPowerShell/v1.0/powershell.exe");
//         addAppCard("Visual Studio Installer", ":/icons/visual_studio.png", "C:/Program Files (x86)/Microsoft Visual Studio/Installer/setup.exe");
//     }
// }

// void AppLauncher::addAppCard(const QString &appName, const QString &iconPath, const QString &appPath) {
//     ClickableWidget *cardWidget = new ClickableWidget;
//     QVBoxLayout *cardLayout = new QVBoxLayout(cardWidget);

//     QLabel *iconLabel = new QLabel;
//     iconLabel->setPixmap(QPixmap(iconPath).scaled(64, 64, Qt::KeepAspectRatio));
//     QLabel *nameLabel = new QLabel(appName);

//     cardLayout->addWidget(iconLabel);
//     cardLayout->addWidget(nameLabel);
//     cardWidget->setLayout(cardLayout);

//     int row = appGridLayout->count() / 5;
//     int col = appGridLayout->count() % 5;
//     appGridLayout->addWidget(cardWidget, row, col);

//     connect(cardWidget, &ClickableWidget::clicked, [this, appPath]() {
//         onAppClicked(appPath);
//     });
// }
