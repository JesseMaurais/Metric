/**
 * Support for LAPACKE, C binding to the Linear Algebra PACKage by Netlib group
 * originally written in Fortran 77.
 */

#include "lux/lux.hpp"
#include "lapacke.hpp"

extern "C" int luaopen_lapack(lua_State *state)
{
	luaL_Reg regs[] =
	{
		// SINGLE PRECISION FLOAT

		#define s(reg) {"s" #reg, lux_cast(reg<float>)},
	
		// LINEAR EQUATIONS
		s(gesv)
		s(gbsv)
		s(gtsv)
		s(posv)
		s(ppsv)
		s(pbsv)
		s(ptsv)
		s(sysv)
		s(spsv)
		// LINEAR LEAST SQUARES
		s(gels)
		s(gelsy)
		s(gelss)
		s(gelsd) 
		// GENERALIZED LINEAR LEAST SQUARES
		s(gglse)
		s(ggglm)
		// EIGENVALUES AND SINGULAR VALUES
		s(gees)
		s(geev)
		s(gesvd)
		s(syev)
		s(spev)
		s(sbev)
		s(stev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		s(gges)
		s(ggev)
		s(ggsvd)
		s(sygv)
		s(spgv)
		s(sbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		s(getrf)
		s(getrf)
	
		// DOUBLE PRECISION FLOAT

		#define d(reg) {"d" #reg, lux_cast(reg<double>)},
	
		// LINEAR EQUATIONS
		d(gesv)
		d(gbsv)
		d(gtsv)
		d(posv)
		d(ppsv)
		d(pbsv)
		d(ptsv)
		d(sysv)
		d(spsv)
		// LINEAR LEAST SQUARES
		d(gels)
		d(gelsy)
		d(gelss)
		d(gelsd)
		// GENERALISED LINEAR LEAST SQUARES
		d(gglse)
		d(ggglm)
		// EIGENVALUES AND SINGULAR VALUES
		d(gees)
		d(geev)
		d(gesvd)
		d(syev)
		d(spev)
		d(sbev)
		d(stev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		d(gges)
		d(ggev)
		d(ggsvd)
		d(sygv)
		d(spgv)
		d(sbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		d(getrf)
		d(getrf)
			
		// SINGLE PRECISION COMPLEX

		#define c(reg) {"c" #reg, lux_cast(reg<complex<float>>)},
	
		// LINEAR EQUATIONS
		c(gesv)
		c(gbsv)
		c(gtsv)
		c(posv)
		c(ppsv)
		c(pbsv)
//		c(ptsv)
		{"cptsv", lux_cast((ptsv<complex<float>, float>))},
		c(sysv)
		c(spsv)
		c(hesv)
		c(hpsv)
		// LINEAR LEAST SQUARES
		c(gels)
//		c(gelsy)
		{"cgelsy", lux_cast((gelsy<complex<float>, float>))},
//		c(gelss)
		{"cgelss", lux_cast((gelss<complex<float>, float>))},
//		c(gelsd)
		{"cgelsd", lux_cast((gelsd<complex<float>, float>))},
		// GENERALISED LINEAR LEAST SQUARES
		c(gglse)
		c(ggglm)
		// EIGENVALUES AND SINGULAR VALUES
		c(gees)
		c(geev)
		c(gesvd)
//		c(heev)
		{"cheev", lux_cast(heev<float>)},
//		c(hpev)
		{"chpev", lux_cast(hpev<float>)},
//		c(hbev)
		{"chbev", lux_cast(hbev<float>)},
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		c(gges)
		c(ggev)
//		c(ggsvd)
		{"cggsvd", lux_cast((ggsvd<complex<float>, float>))},
//		c(hegv)
		{"chegv", lux_cast(hegv<float>)},
//		c(hpgv)
		{"chpgv", lux_cast(hpgv<float>)},
//		c(hbgv)
		{"chbgv", lux_cast(hbgv<float>)},
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		c(getrf)
		c(getrf)
	
		// DOUBLE PRECISION COPMLEX

		#define z(reg) {"z" #reg, lux_cast((reg<complex<double>>))},
	
		// LINEAR EQUATIONS
		z(gesv)
		z(gbsv)
		z(gtsv)
		z(posv)
		z(ppsv)
		z(pbsv)
//		z(ptsv)
		{"cptsv", lux_cast((ptsv<complex<double>, double>))},
		z(sysv)
		z(spsv)
		z(hesv)
		z(hpsv)
		// LINEAR LEAST SQUARES
		z(gels)
//		z(gelsy)
		{"cgelsy", lux_cast((gelsy<complex<double>, double>))},
//		z(gelss)
		{"cgelss", lux_cast((gelss<complex<double>, double>))},
//		z(gelsd)
		{"cgelsd", lux_cast((gelsd<complex<double>, double>))},
		// GENERALISED LINEAR LEAST SQUARES
		z(gglse)
		z(ggglm)
		// EIGENVALUES AND SINGULAR VALUES
		z(gees)
		z(geev)
		z(gesvd)
//		z(heev)
		{"cheev", lux_cast(heev<double>)},
//		z(hpev)
		{"chpev", lux_cast(hpev<double>)},
//		z(hbev)
		{"chbev", lux_cast(hbev<double>)},
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		z(gges)
		z(ggev)
//		z(ggsvd)
		{"cggsvd", lux_cast((ggsvd<complex<double>, double>))},
//		z(hegv)
		{"chegv", lux_cast(hegv<double>)},
//		z(hpgv)
		{"chpgv", lux_cast(hpgv<double>)},
//		z(hbgv)
		{"chbgv", lux_cast(hbgv<double>)},
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		z(getrf)
		z(getrf)
		
		// END
			
		{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

