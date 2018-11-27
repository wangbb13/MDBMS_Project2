@echo off
rem name optinal: corr, inde, anti
rem set name=corr

rem .\main .\datasets\%name%_2.txt .\results\%name%_2_g0.txt 3 0
rem .\main .\datasets\%name%_2.txt .\results\%name%_2_g1.txt 3 1
rem .\main .\datasets\%name%_2.txt .\results\%name%_2_g2.txt 3 2
rem .\main .\datasets\%name%_2.txt .\results\%name%_2_g3.txt 3 3
rem .\main .\datasets\%name%_2.txt .\results\%name%_2_g4.txt 3 4
rem python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g1.txt
rem python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g2.txt
rem python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g3.txt
rem python is_same.py .\results\%name%_2_g0.txt .\results\%name%_2_g4.txt


rem .\main .\datasets\%name%_4.txt .\results\%name%_4_g0.txt 3 0
rem .\main .\datasets\%name%_4.txt .\results\%name%_4_g1.txt 3 1
rem .\main .\datasets\%name%_4.txt .\results\%name%_4_g2.txt 3 2
rem .\main .\datasets\%name%_4.txt .\results\%name%_4_g3.txt 3 3
rem .\main .\datasets\%name%_4.txt .\results\%name%_4_g4.txt 3 4
rem python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g1.txt
rem python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g2.txt
rem python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g3.txt
rem python is_same.py .\results\%name%_4_g0.txt .\results\%name%_4_g4.txt


rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g0.txt 3 0
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g1.txt 3 1
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g2.txt 3 2
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g3.txt 3 3
rem .\main .\datasets\%name%_6.txt .\results\%name%_6_g4.txt 3 4
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g1.txt
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g2.txt
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g3.txt
rem python is_same.py .\results\%name%_6_g0.txt .\results\%name%_6_g4.txt
rem python is_same.py .\results\%name%_6_g1.txt .\results\%name%_6_g2.txt
rem python is_same.py .\results\%name%_6_g2.txt .\results\%name%_6_g3.txt
rem python is_same.py .\results\%name%_6_g3.txt .\results\%name%_6_g4.txt


rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g0.txt 3 0
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g1.txt 3 1
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g2.txt 3 2
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g3.txt 3 3
rem .\main .\datasets\%name%_8.txt .\results\%name%_8_g4.txt 3 4
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g1.txt
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g2.txt
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g3.txt
rem python is_same.py .\results\%name%_8_g0.txt .\results\%name%_8_g4.txt
rem python is_same.py .\results\%name%_8_g1.txt .\results\%name%_8_g2.txt
rem python is_same.py .\results\%name%_8_g2.txt .\results\%name%_8_g3.txt
rem python is_same.py .\results\%name%_8_g3.txt .\results\%name%_8_g4.txt

rem pause


rem ===================  loop version  ===================================
for %%x in (corr inde anti) do (
    echo ================== %%x 2D ================================
    .\main .\datasets\%%x_2.txt .\results\%%x_2_g0.txt 3 0
    .\main .\datasets\%%x_2.txt .\results\%%x_2_g1.txt 3 1
    .\main .\datasets\%%x_2.txt .\results\%%x_2_g2.txt 3 2
    .\main .\datasets\%%x_2.txt .\results\%%x_2_g3.txt 3 3
    .\main .\datasets\%%x_2.txt .\results\%%x_2_g4.txt 3 4
    python is_same.py .\results\%%x_2_g0.txt .\results\%%x_2_g1.txt
    python is_same.py .\results\%%x_2_g0.txt .\results\%%x_2_g2.txt
    python is_same.py .\results\%%x_2_g0.txt .\results\%%x_2_g3.txt
    python is_same.py .\results\%%x_2_g0.txt .\results\%%x_2_g4.txt
    echo ================== %%x 2D END ============================
    echo.
    
    
    echo ================== %%x 4D ================================
    .\main .\datasets\%%x_4.txt .\results\%%x_4_g0.txt 3 0
    .\main .\datasets\%%x_4.txt .\results\%%x_4_g1.txt 3 1
    .\main .\datasets\%%x_4.txt .\results\%%x_4_g2.txt 3 2
    .\main .\datasets\%%x_4.txt .\results\%%x_4_g3.txt 3 3
    .\main .\datasets\%%x_4.txt .\results\%%x_4_g4.txt 3 4
    python is_same.py .\results\%%x_4_g0.txt .\results\%%x_4_g1.txt
    python is_same.py .\results\%%x_4_g0.txt .\results\%%x_4_g2.txt
    python is_same.py .\results\%%x_4_g0.txt .\results\%%x_4_g3.txt
    python is_same.py .\results\%%x_4_g0.txt .\results\%%x_4_g4.txt
    echo ================== %%x 4D END ============================
    echo.
    
    
    echo ================== %%x 6D ================================
    rem .\main .\datasets\%%x_6.txt .\results\%%x_6_g0.txt 3 0
    .\main .\datasets\%%x_6.txt .\results\%%x_6_g1.txt 3 1
    .\main .\datasets\%%x_6.txt .\results\%%x_6_g2.txt 3 2
    .\main .\datasets\%%x_6.txt .\results\%%x_6_g3.txt 3 3
    .\main .\datasets\%%x_6.txt .\results\%%x_6_g4.txt 3 4
    rem python is_same.py .\results\%%x_6_g0.txt .\results\%%x_6_g1.txt
    rem python is_same.py .\results\%%x_6_g0.txt .\results\%%x_6_g2.txt
    rem python is_same.py .\results\%%x_6_g0.txt .\results\%%x_6_g3.txt
    rem python is_same.py .\results\%%x_6_g0.txt .\results\%%x_6_g4.txt
    python is_same.py .\results\%%x_6_g1.txt .\results\%%x_6_g2.txt
    python is_same.py .\results\%%x_6_g2.txt .\results\%%x_6_g3.txt
    python is_same.py .\results\%%x_6_g3.txt .\results\%%x_6_g4.txt
    echo ================== %%x 6D END ============================
    echo.
    
    
    rem echo ================== %%x 8D ================================
    rem .\main .\datasets\%%x_8.txt .\results\%%x_8_g0.txt 3 0
    rem .\main .\datasets\%%x_8.txt .\results\%%x_8_g1.txt 3 1
    rem .\main .\datasets\%%x_8.txt .\results\%%x_8_g2.txt 3 2
    rem .\main .\datasets\%%x_8.txt .\results\%%x_8_g3.txt 3 3
    rem .\main .\datasets\%%x_8.txt .\results\%%x_8_g4.txt 3 4
    rem python is_same.py .\results\%%x_8_g0.txt .\results\%%x_8_g1.txt
    rem python is_same.py .\results\%%x_8_g0.txt .\results\%%x_8_g2.txt
    rem python is_same.py .\results\%%x_8_g0.txt .\results\%%x_8_g3.txt
    rem python is_same.py .\results\%%x_8_g0.txt .\results\%%x_8_g4.txt
    rem python is_same.py .\results\%%x_8_g1.txt .\results\%%x_8_g2.txt
    rem python is_same.py .\results\%%x_8_g2.txt .\results\%%x_8_g3.txt
    rem python is_same.py .\results\%%x_8_g3.txt .\results\%%x_8_g4.txt
    rem echo ================== %%x 8D END ============================
    rem echo.
)

pause