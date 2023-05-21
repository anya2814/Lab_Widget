#include "win.h"

Win::Win(QWidget *parent):QWidget(parent)
{
    codec = QTextCodec::codecForName("UTF-8");                  // для преобразования кодировки текста
    setWindowTitle(codec->toUnicode("Возведение в квадрат"));   // задаем название окна
    frame = new QFrame(this);                                   // создаем рамку для ввода числа
    frame->setFrameShadow(QFrame::Raised);                      // тень вокруг рамки
    frame->setFrameShape(QFrame::Panel);                        // форма рамки
    inputLabel = new QLabel(codec->toUnicode("Введите число:"), // создаем лейбл для строки ввода
        this);
    inputEdit = new QLineEdit("",this);                         // создаем строку ввода
    StrValidator *v=new StrValidator(inputEdit);                // объект для проверки вводимого значения (должна быть строка)
    inputEdit->setValidator(v);                                 // устанавливаем валидатор
    outputLabel = new QLabel(codec->toUnicode("Результат:"),    // создаем лейбл для результата
        this);
    outputEdit = new QLineEdit("",this);                        // создаем пустую строку для вывода результата
    nextButton = new QPushButton(codec->toUnicode("Следующее"), // создаем кнопку для ввода следующего числа
        this);
    exitButton = new QPushButton(codec->toUnicode("Выход"),     // создаем кнопку выход
        this);
    // компоновка приложения выполняется согласно рисунку 2.
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame);             // создаем первый вертикальный компоновщик для рамки и добавляем туда
    vLayout1->addWidget(inputLabel);                            // лейбл для строки ввода
    vLayout1->addWidget(inputEdit);                             // строку ввода
    vLayout1->addWidget(outputLabel);                           // лейбл для результата
    vLayout1->addWidget(outputEdit);                            // строку для результата
    vLayout1->addStretch();                                     // "пружину" для компоновки объектов

    QVBoxLayout *vLayout2 = new QVBoxLayout();                  // создаем первый вертикальный компоновщик для рамки и добавляем туда
    vLayout2->addWidget(nextButton);                            // кнопку "Следующее"
    vLayout2->addWidget(exitButton);                            // кнопку "Выход"
    vLayout2->addStretch();                                     // "пружину" для компоновки объектов

    QHBoxLayout *hLayout = new QHBoxLayout(this);               // создаем горизонтальный компоновщик
    hLayout->addWidget(frame);                                  // добавляем vlayout1 в рамке
    hLayout->addLayout(vLayout2);                               // и vlayout2

    begin();
                                                                // соединение сигналов со слотами
    connect(exitButton,SIGNAL(clicked(bool)),                   // кнопка "Выход" закрывает приложение
        this,SLOT(close()));
    connect(nextButton,SIGNAL(clicked(bool)),                   // кнопка "Следующее" и функция begin()
        this,SLOT(begin()));
    connect(inputEdit,SIGNAL(returnPressed()),                  // кнопка ввода и функция calc()
        this,SLOT(calc()));
}

void Win::begin()
{
    inputEdit->clear();                     // очищение строки ввода
    nextButton->setEnabled(false);          // кнопка "Следующее" блокируется
    nextButton->setDefault(false);          // при нажатии Enter кнопка "Следующее" не активируется
    inputEdit->setEnabled(true);            // строка ввода становится доступной для пользователя
    outputLabel->setVisible(false);         // лейбл строки вывода становится невидимой
    outputEdit->setVisible(false);          // строка вывода тоже становится невидимой
    outputEdit->setEnabled(false);          // строка вывода блокируется
    inputEdit->setFocus();                  // фокусируемся на строке ввода
}

void Win::calc()
{
    bool Ok=true;                           // флаг на корректность ввода
    float r,a;                              // переменные, используемые для обозначения: r - результата, a - введенного числа
    QString str=inputEdit->text();          // получаем введенную строку
    a=str.toDouble(&Ok);                    // проверка на то, что введено число
    if (Ok)
    {
        r=a*a;                              // вычисляем результат
    str.setNum(r);                          // записываем результат в строку
    outputEdit->setText(str);               // выводим str в строку вывода
    inputEdit->setEnabled(false);           // блокируем строку ввода
    outputLabel->setVisible(true);          // делаем видимой лейбл строки вывода
    outputEdit->setVisible(true);           // делаем видимой строку вывода
    nextButton->setDefault(true);           // делаем дефолтной кнопку "Следующее", при нажатии Enter активируется
    nextButton->setEnabled(true);           // кнопка "Следующее" становится доступной для пользователя
    nextButton->setFocus();                 // фокусируемся на кнопке "Следующее"
    }
    else
        if (!str.isEmpty())                 // если строка str не пустая
    {
        QMessageBox msgBox(QMessageBox::Information,            // создаем окно с информацией
            codec->toUnicode("Возведение в квадрат."),          // что было введено неверное значение
            codec->toUnicode("Введено неверное значение."),
            QMessageBox::Ok);                                   // кнопка ok
        msgBox.exec();
    }
}


