#ifndef IMPACTFILTER_H
#define IMPACTFILTER_H

#include <QDialog>

namespace Ui {
class impactFilter;
}

class impactFilter : public QDialog
{
    Q_OBJECT

public:
    explicit impactFilter(QWidget *parent = nullptr);
    ~impactFilter();

private:
    Ui::impactFilter *ui;
};

#endif // IMPACTFILTER_H
