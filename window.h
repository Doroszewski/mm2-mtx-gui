#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QMessageBox>

#include <iostream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
  Q_OBJECT

public:
  Window(QWidget *parent = nullptr);
  ~Window();

  QString openedFile;

  void err(QString text, bool reset);
  void reset();
  void openFile(QString filename);
  void saveFile(QString filename);

private slots:
  void on_actionSpec_triggered();
  void on_actionOpen_triggered();
  void on_actionNew_triggered();
  void on_actionSaveAs_triggered();
  void on_actionSave_triggered();
  void on_actionAbout_triggered();
  void on_actionAboutQt_triggered();

private:
  Ui::Window *ui;
  std::array<QDoubleSpinBox*, 12> allBoxes();
};
#endif // WINDOW_H
