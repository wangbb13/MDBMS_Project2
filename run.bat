@echo off
rem name optinal: corr, inde, anti
set name=inde

.\main .\datasets\%name%_2.txt .\results\%name%_2_g0.txt 3 0
.\main .\datasets\%name%_2.txt .\results\%name%_2_g1.txt 3 1
.\main .\datasets\%name%_2.txt .\results\%name%_2_g2.txt 3 2
python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g1.txt
python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g2.txt


.\main .\datasets\%name%_4.txt .\results\%name%_4_g0.txt 3 0
.\main .\datasets\%name%_4.txt .\results\%name%_4_g1.txt 3 1
.\main .\datasets\%name%_4.txt .\results\%name%_4_g2.txt 3 2
python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g1.txt
python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g2.txt


rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g0.txt 3 0
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g1.txt 3 1
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g2.txt 3 2
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g1.txt
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g2.txt
rem python is_same.py .\results\%name%_6_g1.txt .\results\%name%_6_g2.txt


rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g0.txt 3 0
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g1.txt 3 1
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g2.txt 3 2
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g1.txt
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g2.txt

pause
