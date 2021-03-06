#include "oda.h"

void draw_collapsed_xaya(std::vector<double> &xaya, std::vector<double> &xa, std::vector<double> &xag, std::vector<double> &Bg,  double phi, std::vector<double> &xogxog_Lamg, int na, int p, int p_gamma){

	double sd=sqrt(1/phi);
	std::vector<double> Z(na);
	for(std::vector<double>::iterator it=Z.begin(); it!=Z.end(); ++it) *it=Rf_rnorm(0,1);

	if(p_gamma!=0){
		dgemv_( &transN , &na, &p_gamma, &unity, &*xag.begin(), &na, &*Bg.begin(), &inc, &inputscale0, &*xaya.begin(), &inc);
		daxpy_(&p, &sd, &*Z.begin(), &inc, &*xaya.begin(), &inc);
		Z.resize(p_gamma);
		for(std::vector<double>::iterator it=Z.begin(); it!=Z.end(); ++it) *it=Rf_rnorm(0,1);
		dtrsv_(&uplo, &transN, &unit_tri, &p_gamma, &*xogxog_Lamg.begin(), &p_gamma, &*Z.begin(), &inc);
		dgemv_(&transN , &na, &p_gamma, &sd, &*xag.begin(), &na, &*Z.begin(), &inc, &inputscale1, &*xaya.begin(), &inc);
		//dtrmv_(&uplo, &transT, &unit_tri, &na, &*xa.begin(), &na, &*xaya.begin(), &inc);
		dtpmv_(&uplo, &transT, &unit_tri, &na, &*xa.begin(), &*xaya.begin(), &inc);
	}else{
		for(size_t i=0; i!=xaya.size(); ++i) xaya[i]=sd*Z[i];
		//dtrmv_(&uplo, &transT, &unit_tri, &na, &rxa[0], &na, &*xaya.begin(), &inc);
		dtpmv_(&uplo, &transT, &unit_tri, &na, &*xa.begin(), &*xaya.begin(), &inc);
	}
};
