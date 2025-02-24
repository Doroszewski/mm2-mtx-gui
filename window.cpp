#include "window.h"
#include "ui_window.h"

// Conctructor and destructor
Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window) {
  ui->setupUi(this);
}

Window::~Window() {
  delete ui;
}

// Helper functions
std::array<QDoubleSpinBox*, 12> Window::allBoxes() {
  return {{
    this->ui->g1_x,
    this->ui->g1_y,
    this->ui->g1_z,
    this->ui->g2_x,
    this->ui->g2_y,
    this->ui->g2_z,
    this->ui->g3_x,
    this->ui->g3_y,
    this->ui->g3_z,
    this->ui->g4_x,
    this->ui->g4_y,
    this->ui->g4_z,
  }};
}

void Window::err(QString text, bool reset = false)  {
  QMessageBox dialog;
  dialog.setIcon(QMessageBox::Critical);
  dialog.setText(text);
  if (reset)
    this->reset();
  dialog.exec();
}

// Triggers
void Window::on_actionNew_triggered() {
  for (QDoubleSpinBox* b : this->allBoxes()) {
    b->setEnabled(true);
    b->setValue(0.0);
  }
  this->ui->actionSave->setEnabled(true);
  this->ui->actionSaveAs->setEnabled(true);
  this->ui->buttonSave->setEnabled(true);
}

void Window::on_actionOpen_triggered() {
  QString filename = QFileDialog::getOpenFileName(this, "Open MTX file", ".", "MTX files (*.mtx)");
  if (!filename.isNull())
    this->openFile(filename);
}

void Window::on_actionSave_triggered() {
  if (this->openedFile == "") {
    QString filename = QFileDialog::getSaveFileName(this, "Save file", "untitled.mtx", "MTX files (*.mtx)");
    this->saveFile(filename);
  } else {
    this->saveFile(this->openedFile);
  }
}

void Window::on_actionSaveAs_triggered() {
  QString filename = QFileDialog::getSaveFileName(this, "Save file", "untitled.mtx", "MTX files (*.mtx)");
  this->saveFile(filename);
}

void Window::on_actionSpec_triggered() {
  QString url = "https://github.com/Dummiesman/angel-file-formats/blob/master/Midtown%20Madness%202/MTX.md";
  QDesktopServices::openUrl(QUrl(url));
}

void Window::on_actionAbout_triggered()
{
  QMessageBox::about(this, "About MTX Editor",
                     "<b>MTX Editor</b>, 0.1<br />"
                     "Simple editor of MTX files used by "
                     "Angel Studios games<br /><br />"
                     "© 2025 Piotr “Drogosław” Doroszewski, "
                     "distributed under the MIT license<br/><br/>"
                     "Join <a href=\"https://discord.gg/hFsM2WVThW\">"
                     "the Midtown Club “server” on Discord</a> for more information");
}

void Window::on_actionAboutQt_triggered() {
  QMessageBox::aboutQt(this);
}


// Proper functions
void Window::reset() {
  for (QDoubleSpinBox* b : this->allBoxes()) {
    b->setDisabled(true);
  }
  this->ui->actionSave->setDisabled(true);
  this->ui->actionSaveAs->setDisabled(true);
  this->ui->buttonSave->setDisabled(true);
  this->openedFile = "";
  this->setWindowTitle("MTX Editor");
}

void Window::openFile(QString filename) {
  std::ifstream file;
  float tmp;
  file.open(filename.toStdString(), std::ios::binary);
  if (!file.good()) {
    this->err("Cannot open the selected file!", 1);
    return;
  }
  for (QDoubleSpinBox* b : this->allBoxes()) {
    file.read((char*)&tmp, sizeof(float));
    b->setEnabled(true);
    b->setValue(tmp);
  }
  if (file.fail()) {
    this->err("This doesn't look like a correct MTX file!", 1);
    return;
  }

  file.read((char*)&tmp, sizeof(float)); // wait for EOF
  if (!file.eof()) {
    this->err("This doesn't look like a correct MTX file! It's too big!", 1);
    return;
  }
  this->ui->actionSave->setEnabled(true);
  this->ui->actionSaveAs->setEnabled(true);
  this->ui->buttonSave->setEnabled(true);
  this->openedFile = filename;
  this->setWindowTitle(filename.prepend("MTX Editor – "));
}

void Window::saveFile(QString filename) {
  float values[12];

  unsigned char x = 0;
  for (QDoubleSpinBox* b : this->allBoxes()) {
    values[x] = b->value();
    x++;
  }

  std::ofstream file;
  file.open(filename.toStdString(), std::ios::binary);
  file.write((char*)values, 48);
}

