/**
 * Support for LAPACKE, C binding to the Linear Algebra PACKage by Netlib group
 * originally written in Fortran 77.
 *
 * TODO: Not all of the routines are here and we need to check that they work.
 */

#include "lux/lux.hpp"
#include <complex>

template <class real> using complex = std::complex<real>;

#define lapack_complex_double complex<double>
#define lapack_complex_float complex<float>
#define lapack_logical bool
#define lapack_int int
#define LAPACK_COMPLEX_CUSTOM

#include <lapacke.h>

// MODULE ENTRY POINT /////////////////////////////////////////////////////////

#define REG(reg) {#reg, lux_cast(LAPACKE_##reg)},

extern "C" int luaopen_lapack(lua_State *state)
{
	luaL_Reg regs[] =
	{
		/** SINGLE PRECISION FLOAT **/
	
		// LINEAR EQUATIONS
		REG(sgesv)
		REG(sgbsv)
		REG(sgtsv)
		REG(sposv)
		REG(sppsv)
		REG(spbsv)
		REG(sptsv)
		REG(ssysv)
		REG(sspsv)
		// LINEAR LEAST SQUARES
		REG(sgels)
		REG(sgelsy)
		REG(sgelss)
		REG(sgelsd) 
		// GENERALIZED LINEAR LEAST SQUARES
		REG(sgglse)
		REG(sggglm)
		// EIGENVALUES AND SINGULAR VALUES
		REG(sgees)
		REG(sgeev)
		REG(sgesvd)
		REG(ssyev)
		REG(sspev)
		REG(ssbev)
		REG(sstev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		REG(sgges)
		REG(sggev)
		REG(sggsvd)
		REG(ssygv)
		REG(sspgv)
		REG(ssbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		REG(sgetrf)
		REG(sgetrf)
	
		/** DOUBLE PRECISION FLOAT **/
	
		// LINEAR EQUATIONS
		REG(dgesv)
		REG(dgbsv)
		REG(dgtsv)
		REG(dposv)
		REG(dppsv)
		REG(dpbsv)
		REG(dptsv)
		REG(dsysv)
		REG(dspsv)
		// LINEAR LEAST SQUARES
		REG(dgels)
		REG(dgelsy)
		REG(dgelss)
		REG(dgelsd)
		// GENERALISED LINEAR LEAST SQUARES
		REG(dgglse)
		REG(dggglm)
		// EIGENVALUES AND SINGULAR VALUES
		REG(dgees)
		REG(dgeev)
		REG(dgesvd)
		REG(dsyev)
		REG(dspev)
		REG(dsbev)
		REG(dstev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		REG(dgges)
		REG(dggev)
		REG(dggsvd)
		REG(dsygv)
		REG(dspgv)
		REG(dsbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		REG(dgetrf)
		REG(dgetrf)
			
		/** SINGLE PRECISION COMPLEX **/
	
		// LINEAR EQUATIONS
		REG(cgesv)
		REG(cgbsv)
		REG(cgtsv)
		REG(cposv)
		REG(cppsv)
		REG(cpbsv)
		REG(cptsv)
		REG(csysv)
		REG(cspsv)
		REG(chesv)
		REG(chpsv)
		// LINEAR LEAST SQUARES
		REG(cgels)
		REG(cgelsy)
		REG(cgelss)
		REG(cgelsd)
		// GENERALISED LINEAR LEAST SQUARES
		REG(cgglse)
		REG(cggglm)
		// EIGENVALUES AND SINGULAR VALUES
		REG(cgees)
		REG(cgeev)
		REG(cgesvd)
		REG(cheev)
		REG(chpev)
		REG(chbev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		REG(cgges)
		REG(cggev)
		REG(cggsvd)
		REG(chegv)
		REG(chpgv)
		REG(chbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		REG(cgetrf)
		REG(cgetrf)
	
		/** DOUBLE PRECISION COPMLEX **/
	
		// LINEAR EQUATIONS
		REG(zgesv)
		REG(zgbsv)
		REG(zgtsv)
		REG(zposv)
		REG(zppsv)
		REG(zpbsv)
		REG(zptsv)
		REG(zsysv)
		REG(zspsv)
		REG(zhesv)
		REG(zhpsv)
		// LINEAR LEAST SQUARES
		REG(zgels)
		REG(zgelsy)
		REG(zgelss)
		REG(zgelsd)
		// GENERALISED LINEAR LEAST SQUARES
		REG(zgglse)
		REG(zggglm)
		// EIGENVALUES AND SINGULAR VALUES
		REG(zgees)
		REG(zgeev)
		REG(zgesvd)
		REG(zheev)
		REG(zhpev)
		REG(zhbev)
		// GENERALIZED EIGENVALUES AND SINGULAR VALUES
		REG(zgges)
		REG(zggev)
		REG(zggsvd)
		REG(zhegv)
		REG(zhpgv)
		REG(zhbgv)
		// COMPUTATIONAL ROUTINES FOR LINEAR EQUATIONS
		REG(zgetrf)
		REG(zgetrf)
		
		// END
			
		{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

