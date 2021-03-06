#include "oda.h"

void draw_xoyo(const std::vector<double> &Z, std::vector<double> &xoyo, double &yobar, std::vector<double> &xo, std::vector<double> &xog, std::vector<double> Bg,  double phi, int no, int p, int p_gamma,double intercept)
{
	std::vector<double> U(no);
	for(std::vector<double>::iterator it=U.begin(); it!=U.end(); ++it) *it=Rf_runif(0,1);
	std::vector<double> yo(no,intercept);

	//Set Mean Values//
	if(p_gamma!=0)	dgemv_(&transN , &no, &p_gamma, &unity, &*xog.begin(), &no, &*Bg.begin(), &inc, &inputscale1, &*yo.begin(), &inc);

	for (size_t i = 0; i < Z.size(); ++i)
	{
		double Fa=pnorm(-yo[i],0,1,1,0);
		if(Z[i]==1){
			yo[i]+=qnorm(Fa+U[i]*(1-Fa),0,1,1,0);
		}else{
			yo[i]+=qnorm(U[i]*Fa,0,1,1,0);
		}

	}

	yobar=center_yo(yo);

	//Multiply by Xo'//
	dgemv_( &transT, &no, &p, &unity, &*xo.begin(), &no, &*yo.begin(), &inc, &inputscale0, &*xoyo.begin(), &inc);
}
