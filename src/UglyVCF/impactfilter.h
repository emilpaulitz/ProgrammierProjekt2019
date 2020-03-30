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

    void openWindow(QString region);

    double getHigh();

    double getModerate();

    double getLow();

    double getModifier();

    double getUnknown();

    bool isFilterByImpact();

private slots:
    void on_resetButton_clicked();

private:
    Ui::impactFilter *ui;
    bool filterByImpact= true;
};

#endif // IMPACTFILTER_H
