mkdir plots
gcc 170010054.c -lm
./a.out 1
./a.out 2
./a.out 3
python error_plots.py 0
python mid_line_plots.py 0
