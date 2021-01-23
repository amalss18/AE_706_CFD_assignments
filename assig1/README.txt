To generate the results given in the report follow the steps given below:

1) To generate all the plots:
	i) Run the following commands in the directory containing 170010054.py and 170010054.cpp
		$ chmod +x gen_plots.sh
		$ ./gen_plots.sh
	ii) All the plots will be available in a folder named plots.

	Incase the above steps don't work do the following steps:
	i) create empty directories named data and plots
	ii) Run the following commands:
		$ g++ 170010054.cpp
		$ ./a.out 0
		$ python 170010054.py

2) To generate plot for a specific case
	i) Create new empty directories named data and plots
	ii) Compile 170010054.cpp as
		$ g++ 170010054.py
	iii) Execute the program passing in three arguments for scheme, initial condition and m value
		The numbering system for the arguments is a follows:
		Scheme: 
			1 - FTFS
			2 - FTCS
			3 - FTBS
			4 - LW
			5 - BW
			6 - Fromm
		Initial condition:
			1 - Step
			2 - 2 periods
			3 - 4 periods
			4 - 6 periods
			5 - Gaussian
	 
		Examples: 
		a) If you want to generate the data for the FTBS scheme, for a Gaussian with CFl number 0.5, you should run:
			$ ./a.out 3 5 0.5
		b) If you want to generate the data for the Fromm scheme, for 4 period sinusoidal with CFl number 1.0, you should run:
			$ ./a.out 6 3 1.0

	iv) Generate the plot by running the following command:
		$ python 170010054.py file_name

		where file_name is of the following format: schemeX-ICY-muZ.csv
		where X, Y, Z are the scheme number, initial condition number, CFL number following the same convention as in point iii

		Example: Taking the same case as in the previous example a), you will need to run:
			$ python 170010054.py scheme3-IC5-mu0.5.csv

	v) Find the plot in the plots directory.	


