# MoneyMaze 

> Разбирайтесь в различных финансовых сценариях, принимайте решения и узнайте, как построить надежное финансовое будущее!

**Авторы**: [`Швец М.`](https://github.com/marr97), [`Томилова А.`](https://github.com/alinatomilova)


## Описание

**MoneyMaze** — кроссплатформенное приложение для обучения финансовой грамотности в игровой форме. Основная функциональность включает симуляцию личного бюджета с ежемесячным циклом, систему кредитов и вкладов, обучающие модули и визуализацию финансового состояния пользователя.


## Архитектура

Приложение состоит из двух основных компонентов:

* Десктопная часть - кроссплатформенное Qt-приложение, работающее на Windows / Linux / macOS
* Серверная часть - обрабатывает запросы от клиента и хранит данные пользователей в PostgreSQL

Весь прогресс игры каждого пользователя сохраняется в базе данных на бэкенде, что позволяет синхронизировать данные между разными устройствами.


## Функциональности проекта

* Обучающие модули:

<img src="https://github.com/marr97/MoneyMaze/blob/main/screenshots/module.png" width="50%"/>

* Возможность оформить кредит или вклад, а так же просмотреть информацию по ним:

<img src="https://github.com/marr97/MoneyMaze/blob/main/screenshots/loan.png" width="48%"/> <img src="https://github.com/marr97/MoneyMaze/blob/main/screenshots/loan_info.png" width="48%"/>

* Финансовая диаграмма пользователя:

<img src="https://github.com/marr97/MoneyMaze/blob/main/screenshots/home_screen.png" width="100%"/>


## Используемые технологии

* Интерфейс: `Qt 6`
* База данных: `PostgreSQL`
* Сеть: `Poco Libraries`
* Система сборки: `Cmake`


## Установка приложения и его запуск

> Предполагается сборка серверной и десктопной частей по отдельности

1. Установите необходмые пакеты _(ниже команда для сборки на Linux)_

```bash
sudo apt-get install build-essential libgl1-mesa-dev pkg-config libpqxx-dev qt6-base-dev cmake
```

2. Склонируйте репозиторий

```bash
git clone https://github.com/marr97/MoneyMaze
```

3. Перейдите в серверную часть `MoneyMaze/Server` или десктопную `MoneyMaze/Desktop` и соберите

```bash
cd MoneyMaze/Server
mkdir build && cd build
cmake ..
make
```

4. Для запуска сервера выполните команду

```bash
./MoneyMazeServer 
```