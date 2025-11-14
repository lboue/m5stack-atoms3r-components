@echo off

echo Starting the Virtual Environment
python -m venv .venv

echo Activating the Virtual Environment
call .venv\Scripts\activate

:install

echo Installing required packages...

python.exe -m pip install --upgrade pip

pip3 install -r requirements.txt