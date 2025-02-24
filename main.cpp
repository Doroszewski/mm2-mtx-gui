#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QCommandLineParser>

#include "window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QCommandLineParser parser;
  Window w;

  a.setApplicationName("MTX Editor");
  a.setApplicationVersion("0.1");

  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "MTX file to open");

  /*parser.addOptions({
          {{"c", "csv"}, "output CSV"}
  });*/


  parser.process(a);

  w.show();
  w.reset();
  if (parser.positionalArguments().size() == 1)
    w.openFile(parser.positionalArguments().at(0));

  return a.exec();
}
