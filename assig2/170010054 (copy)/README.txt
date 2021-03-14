To generate the plots and the data file (.txt), follow the steps given below:

1) Make sure all the python and the C files are in one directory

2) Type in the following commands into the commmand line:
	a) chmod +x generate_plots_and_data.sh
	b) ./generate_plots_and_data.sh

3) You should see all the plots being generated. You can also find them saved in a folder called plots.

4) To generate the contour plots, use the data files converged_jacobi.csv, converged_gauss_seidel.csv, converged_SOR.csv

5) Open the .csv file in Paraview, use the filter TabletoPoints, then use the Delauny2D filter, and finally use the Countour filter. Set the contour values to 5, 10, 25, 50, 100, 150, 200, 250 to generate the required plots given in the contour_plots folder.

This should work without any issues. Incase some problem arises, kindly contact me at 170010054@iitb.ac.in
