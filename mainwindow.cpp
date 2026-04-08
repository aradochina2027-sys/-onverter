#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDoubleValidator>
#include <QSignalBlocker>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupLogic();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupLogic() {
    QDoubleValidator *val = new QDoubleValidator(this);
    val->setLocale(QLocale::C);

    QLineEdit* edits[] = {
        ui->editTopL, ui->editBottomL,
        ui->editTopM, ui->editBottomM,
        ui->editTopT, ui->editBottomT
    };
    for(auto e : edits) e->setValidator(val);

    connect(ui->editTopL, &QLineEdit::textEdited, this, &MainWindow::onTopChanged);
    connect(ui->editBottomL, &QLineEdit::textEdited, this, &MainWindow::onBottomChanged);
    connect(ui->editTopM, &QLineEdit::textEdited, this, &MainWindow::onTopChanged);
    connect(ui->editBottomM, &QLineEdit::textEdited, this, &MainWindow::onBottomChanged);
    connect(ui->editTopT, &QLineEdit::textEdited, this, &MainWindow::onTopChanged);
    connect(ui->editBottomT, &QLineEdit::textEdited, this, &MainWindow::onBottomChanged);

    connect(ui->comboTopUnitL, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);
    connect(ui->comboBottomUnitL, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);
    connect(ui->comboTopUnitM, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);
    connect(ui->comboBottomUnitM, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);
    connect(ui->comboTopUnitT, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);
    connect(ui->comboBottomUnitT, &QComboBox::currentIndexChanged, this, &MainWindow::updateCurrentTab);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::updateCurrentTab);
}

void MainWindow::onTopChanged() { doConvert(true); }
void MainWindow::onBottomChanged() { doConvert(false); }
void MainWindow::updateCurrentTab() { doConvert(true); }

void MainWindow::doConvert(bool topToBottom) {
    int tab = ui->tabWidget->currentIndex();
    QLineEdit *src, *dest;
    QComboBox *cSrc, *cDest;

    if (tab == 0) {
        src = topToBottom ? ui->editTopL : ui->editBottomL;
        dest = topToBottom ? ui->editBottomL : ui->editTopL;
        cSrc = topToBottom ? ui->comboTopUnitL : ui->comboBottomUnitL;
        cDest = topToBottom ? ui->comboBottomUnitL : ui->comboTopUnitL;
    } else if (tab == 1) {
        src = topToBottom ? ui->editTopM : ui->editBottomM;
        dest = topToBottom ? ui->editBottomM : ui->editTopM;
        cSrc = topToBottom ? ui->comboTopUnitM : ui->comboBottomUnitM;
        cDest = topToBottom ? ui->comboBottomUnitM : ui->comboTopUnitM;
    } else {
        src = topToBottom ? ui->editTopT : ui->editBottomT;
        dest = topToBottom ? ui->editBottomT : ui->editTopT;
        cSrc = topToBottom ? ui->comboTopUnitT : ui->comboBottomUnitT;
        cDest = topToBottom ? ui->comboBottomUnitT : ui->comboTopUnitT;
    }

    bool ok;
    double val = src->text().toDouble(&ok);
    if (!ok) {
        QSignalBlocker b(dest);
        dest->clear();
        return;
    }

    double res = Converter::convert(val, (Converter::Mode)tab, cSrc->currentText(), cDest->currentText());
    QSignalBlocker b(dest);
    dest->setText(QString::number(res, 'g', 10));
}
