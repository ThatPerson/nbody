set terminal png
do for [t=0:415] {
	outfile = sprintf("animation/t-%03.0f.png", t)
	set output outfile
	in1 = sprintf("<(sed -n '1,%dp' t-0.csv)", t)
	in2 = sprintf("<(sed -n '1,%dp' t-1.csv)", t)
	in3 = sprintf("<(sed -n '1,%dp' t-2.csv)",  t)
	in4 = sprintf("<(sed -n '1,%dp' t-3.csv)", t)
	splot in1 using 2:3:4 w lines, in2 u 2:3:4 w lines, in3 u 2:3:4 w lines, in4 u 2:3:4 w lines
}
