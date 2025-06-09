#include "loan_module.h"
#include "ui_loan_module.h"
#include <QString>
#include <QFont>
#include <QTimer>
#include <QLabel>


loan_module::loan_module(QWidget *parent)
    : QWidget(parent), ui(new Ui::loan_module) {
    ui->setupUi(this);
    this->setWindowTitle("Модуль о кредитах");

    QString buttonStyle =
        "QPushButton {"
        "   background-color: rgba(174, 208, 180, 0.5);"
        "   border-top: none;"
        "   text-align: center;"
        "   color: rgba(97, 197, 84, 0.9);"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(151, 207, 169, 0.6)"
        "}";

    ui->pb_next->setStyleSheet(buttonStyle);

    // Тексты и заголовки модуля

    QFont headingFont("Gill Sans", 16, QFont::Bold);
    QFont textFont("Gill Sans", 14);


    ui->ql_heading->setFont(headingFont);
    ui->ql_heading->setStyleSheet("color: rgb(97, 197, 84);");
    ui->ql_text->setFont(textFont);

    ui->ql_text->setWordWrap(true);
    ui->ql_text->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    ui->ql_heading->setAlignment(Qt::AlignCenter);
    ui->ql_text->setContentsMargins(10, 5, 10, 5);
    ui->ql_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    QString heading_0 = "Зачем нужен кредит?";

    QString heading_1 = "Почему взять кредит выгоднее, чем копить?";

    QString heading_2 = "Банковская форма кредитования";

    QString heading_3 = "Нюансы выдачи кредита";

    QString heading_4 = "Как получить кредит?";

    QString text_0 = "<div style='font-family: Gill Sans; font-size: 16pt; line-height: 1.5; margin: 0;'>"
        "Если вам не хватает средств на приобретение нужных товаров, "
        "реализацию крупных целей, можно обратиться в банк. "
        "Вам выдадут необходимую сумму под проценты!"
        "</div>";

    QString text_1 = "<div style='font-family: Gill Sans; font-size: 16pt; line-height: 1.5; margin: 0;'>"
        "Иногда люди предвзято относятся к кредитованию "
        "и предпочитают копить самостоятельно. "
        "Но это не всегда выгодно: пока собирается сумма, "
        "товар может подорожать или исчезнуть из продажи. "
        "Потребительский кредит — удобный финансовый инструмент!"
        "</div>";

    QString text_2 = "<div style='font-family: Gill Sans; font-size: 16pt; line-height: 1.5; margin: 0;'>"
        "Средства выдают физическим и юридическим лицам. "
        "Процентную ставку устанавливает банк "
        "на основе предложения и ключевой ставки"
        "</div>";

    QString text_3 = "<div style='font-family: Gill Sans; font-size: 16pt; line-height: 1.5; margin: 0;'>"
        "<div style='text-align: center; margin-bottom: 5px;'>Перед одобрением займа банк проверяет:</div>"
        "<ul style='margin-top: 0; margin-bottom: 2px; margin-left: 10px; padding-left: 10px;'>"
        "<li style='margin-bottom: 3px;'>Платежеспособность - доходы клиента</li>"
        "<li style='margin-bottom: 3px;'>Кредитную историю. Желательно, чтобы у клиента не было просрочек по выплатам</li>"
        "<li>Текущие финансовые обязательства</li>"
        "</ul>"
        "</div>";

    QString text_4 = "<div style='font-family: Gill Sans; font-size: 16pt; line-height: 1.5; margin: 0;'>"
        "<div style='text-align: center; margin-bottom: 5px;'>Чтобы оформить кредит:</div>"
        "<ul style='margin-top: 0; margin-bottom: 2px; margin-left: 10px; padding-left: 10px;'>"
        "<li style='margin-bottom: 3px;'>Нажмите кнопку «оформить» на главном экране</li>"
        "<li style='margin-bottom: 3px;'>Выберите сумму и количество месяцев для выплат</li>"
        "<li style='margin-bottom: 2px;'>Получите одобрение на взятие кредита</li>"
        "<li>Используйте средства</li>"
        "</ul>"
        "</div>";

    ui->ql_text->setTextFormat(Qt::RichText);

    headings << heading_0 << heading_1 << heading_2 << heading_3 << heading_4;

    texts << text_0 << text_1 << text_2 << text_3 << text_4;

    ui->ql_heading->setText(headings[heading_id]);
    ui->ql_text->setText(texts[text_id]);


    text_opacity_effect = new QGraphicsOpacityEffect(this);
    text_opacity_effect->setOpacity(1.0);
    ui->ql_heading->setGraphicsEffect(text_opacity_effect);
    ui->ql_text->setGraphicsEffect(text_opacity_effect);


    fade_out = new QPropertyAnimation(text_opacity_effect, "opacity", this);
    fade_out->setDuration(500);
    fade_out->setStartValue(1.0);
    fade_out->setEndValue(0.0);

    fade_in = new QPropertyAnimation(text_opacity_effect, "opacity", this);
    fade_in->setDuration(500);
    fade_in->setStartValue(0.0);
    fade_in->setEndValue(1.0);

    connect(ui->pb_next, &QPushButton::clicked, this, &loan_module::on_pb_next_clicked);
    connect(fade_out, &QPropertyAnimation::finished, this, &loan_module::fade_out_text_finished);

}

loan_module::~loan_module() {
    delete ui;
}

void loan_module::on_pb_next_clicked()
{
    if (text_id == text_last_id){
        loan_module_finished();
    }
    else {
        fade_out->start();
    }
}

void loan_module::fade_out_text_finished()
{
    heading_id = (heading_id + 1) % headings.size();
    ui->ql_heading->setText(headings[heading_id]);

    text_id = (text_id + 1) % texts.size();
    ui->ql_text->setText(texts[text_id]);

    if (text_id == text_last_id){
        ui->pb_next->setText("Завершить");
    }

    fade_in->start();
}


void loan_module::loan_module_finished()
{

    const int timeout_ms = 3600;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(60);
    QString message = "Поздравляем с завершением модуля!\n"
        "Теперь вы готовы взять кредит, если потребуется";
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);

    label->setStyleSheet(
        "background-color: rgb(97, 197, 84);"
        "color: rgb(255, 255, 255);"
        "border-radius: 5px;"
        "padding: 10px;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 14px;"
        );

    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 4;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);

    QTimer::singleShot(timeout_ms, this, [this]{
        this->hide();
    });
}



