/* boost random/mixmax.hpp header file
 *
 * Copyright Kostas Savvidis 2008-2019
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2019-04-23 created
 */

#ifndef BOOST_RANDOM_MIXMAX_HPP
#define BOOST_RANDOM_MIXMAX_HPP

#include <sstream>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>

#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template mixmax_engine model,
 * \pseudo_random_number_generator .
 *  It uses the  MIXMAX generator algorithms from:
 *
 *  @blockquote
 *  G.K.Savvidy and N.G.Ter-Arutyunian,
 *  On the Monte Carlo simulation of physical systems,
 *  J.Comput.Phys. 97, 566 (1991);
 *  Preprint EPI-865-16-86, Yerevan, Jan. 1986
 *  http://dx.doi.org/10.1016/0021-9991(91)90015-D
 *
 *  K.Savvidy
 *  The MIXMAX random number generator
 *  Comp. Phys. Commun. 196 (2015), pp 161–165
 *  http://dx.doi.org/10.1016/j.cpc.2015.06.003
 *
 *  K.Savvidy and G.Savvidy
 *  Spectrum and Entropy of C-systems. MIXMAX random number generator
 *  Chaos, Solitons & Fractals, Volume 91, (2016) pp. 33–38
 *  http://dx.doi.org/10.1016/j.chaos.2016.05.003
 *  @endblockquote
 *
 * The generator crucially depends on the choice of the
 * parameters. The valid sets of parameters are from the published papers above.
 *
 */

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> // MIXMAX TEMPLATE PARAMETERS
class mixmax_engine{
public:
    // Interfaces required by C++11 std::random and boost::random
    typedef boost::uint64_t result_type ;
    BOOST_STATIC_CONSTANT(boost::uint64_t,mixmax_min=0);
    BOOST_STATIC_CONSTANT(boost::uint64_t,mixmax_max=((1ULL<<61)-1));
    BOOST_STATIC_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION() {return mixmax_min;}
    BOOST_STATIC_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION() {return mixmax_max;}
    static const bool has_fixed_range = false;
    BOOST_STATIC_CONSTANT(int,N=Ndim);     ///< The main internal parameter, size of the defining MIXMAX matrix
    // CONSTRUCTORS:
    explicit mixmax_engine();                       ///< Constructor, unit vector as initial state, acted on by A^2^512
    explicit mixmax_engine(boost::uint64_t);          ///< Constructor, one 64-bit seed
    explicit mixmax_engine(uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID );  ///< Constructor, four 32-bit seeds for 128-bit seeding flexibility
    void seed(boost::uint64_t seedval=default_seed){seed_uniquestream( &S, 0, 0, (uint32_t)(seedval>>32), (uint32_t)seedval );} ///< seed with one 64-bit seed
    
private: // DATATYPES
    struct rng_state_st{
        boost::array<boost::uint64_t, Ndim> V;
        boost::uint64_t sumtot;
        int counter;
    };
    
    typedef struct rng_state_st rng_state_t;     // struct alias
    rng_state_t S;
    
public: // SEEDING FUNCTIONS
    template<class It> mixmax_engine(It& first, It last) { seed(first,last); }
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(mixmax_engine,  SeedSeq, seq){ seed(seq); }
    
    /** Sets the state of the generator using values from an iterator range. */
    template<class It>
    void seed(It& first, It last){
        uint32_t v[4];
        detail::fill_array_int<32>(first, last, v);
        seed_uniquestream( &S, v[0], v[1], v[2], v[3]);
    }
    /** Sets the state of the generator using values from a seed_seq. */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(mixmax_engine, SeeqSeq, seq){
        uint32_t v[4];
        detail::seed_array_int<32>(seq, v);
        seed_uniquestream( &S, v[0], v[1], v[2], v[3]);
    }
    
    /** return one uint64 between min=0 and max=2^61-1 */
    boost::uint64_t operator()(){
        if (S.counter<=(Ndim-1) ){
            return S.V[S.counter++];
        }else{
            S.sumtot = iterate_raw_vec(S.V.data(), S.sumtot);
            S.counter=2;
            return S.V[1];
        }
    }
    
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last) { detail::generate_from_int(*this, first, last); }
    
    void discard(boost::uint64_t nsteps) { for(boost::uint64_t j = 0; j < nsteps; ++j)  (*this)(); } ///< discard n steps, required in boost::random
    
    /** save the state of the RNG to a stream */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<< (std::basic_ostream<CharT,Traits>& ost, const mixmax_engine& me){
        ost << Ndim << " " << me.S.counter << " " << me.S.sumtot << " ";
        for (int j=0; (j< (Ndim) ); j++) {
        ost <<  (boost::uint64_t)me.S.V[j] << " ";
        }
        ost << "\n";
        ost.flush();
        return ost;
        }
        
    /** read the state of the RNG from a stream */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>> (std::basic_istream<CharT,Traits> &in, mixmax_engine& me){
        // will set std::ios::failbit if the input format is not right
        boost::array<boost::uint64_t, Ndim> vec;
        boost::uint64_t sum=0, savedsum=0, counter=0;
        in >> counter >> std::ws;
        BOOST_ASSERT(counter==Ndim);
        in >> counter >> std::ws;
        in >> savedsum >> std::ws;
        for(int j=0;j<Ndim;j++) {
        in >> std::ws >> vec[j] ;
        sum=me.MOD_MERSENNE(sum+vec[j]);
    }
    if (sum == savedsum && counter>0 && counter<Ndim){
        me.S.V=vec; me.S.counter = counter; me.S.sumtot=savedsum;
    }else{
        in.setstate(std::ios::failbit);
    }
    return in;
    }

friend bool operator==(const mixmax_engine & x,
                       const mixmax_engine & y){return x.S.counter==y.S.counter && x.S.sumtot==y.S.sumtot && x.S.V==y.S.V ;}
friend bool operator!=(const mixmax_engine & x,
                       const mixmax_engine & y){return !operator==(x,y);}


private:
BOOST_STATIC_CONSTANT(int, BITS=61);
BOOST_STATIC_CONSTANT(boost::uint64_t, M61=2305843009213693951ULL);
BOOST_STATIC_CONSTANT(boost::uint64_t, default_seed=1);
inline boost::uint64_t MOD_MERSENNE(boost::uint64_t k) {return ((((k)) & M61) + (((k)) >> BITS) );}
inline boost::uint64_t MULWU(boost::uint64_t k);
inline void seed_vielbein(rng_state_t* X, unsigned int i); // seeds with the i-th unit vector, i = 0..Ndim-1,  for testing only
inline void seed_uniquestream( rng_state_t* Xin, uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID );
inline boost::uint64_t iterate_raw_vec(boost::uint64_t* Y, boost::uint64_t sumtotOld);
inline boost::uint64_t apply_bigskip(boost::uint64_t* Vout, boost::uint64_t* Vin, uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID );
inline boost::uint64_t modadd(boost::uint64_t foo, boost::uint64_t bar);
inline boost::uint64_t fmodmulM61(boost::uint64_t cum, boost::uint64_t s, boost::uint64_t a);
};

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::mixmax_engine()
///< constructor, with no params, seeds with seed=0,  random numbers are as good as from any other seed
{
    seed_uniquestream( &S, 0,  0, 0, default_seed);
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::mixmax_engine(boost::uint64_t seedval){
    ///< constructor, one uint64_t seed, random numbers are statistically independent from any two distinct seeds, e.g. consecutive seeds are ok
    seed_uniquestream( &S, 0,  0,  (uint32_t)(seedval>>32), (uint32_t)seedval );
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::mixmax_engine(uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID){
    // constructor, four 32-bit seeds for 128-bit seeding flexibility
    seed_uniquestream( &S, clusterID,  machineID,  runID,  streamID );
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> uint64_t mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::MULWU (uint64_t k){ return (( (k)<<(SPECIALMUL) & M61) ^ ( (k) >> (BITS-SPECIALMUL))  )  ;}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> boost::uint64_t mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::iterate_raw_vec(boost::uint64_t* Y, boost::uint64_t sumtotOld){
    // operates with a raw vector, uses known sum of elements of Y
    boost::uint64_t  tempP=0, tempV=sumtotOld;
    Y[0] = tempV;
    boost::uint64_t sumtot = Y[0], ovflow = 0; // will keep a running sum of all new elements
    for (int i=1; i<Ndim; i++){
        boost::uint64_t tempPO = MULWU(tempP);
        tempV = (tempV+tempPO);
        tempP = modadd(tempP, Y[i]);
        tempV = modadd(tempV, tempP); // new Y[i] = old Y[i] + old partial * m
        Y[i] = tempV;
        sumtot += tempV; if (sumtot < tempV) {ovflow++;}
    }
    return MOD_MERSENNE(MOD_MERSENNE(sumtot) + (ovflow <<3 ));
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> void mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::seed_vielbein(rng_state_t* X, unsigned int index){
    for (int i=0; i < Ndim; i++){
        X->V[i] = 0;
    }
    if (index<Ndim) { X->V[index] = 1; }else{ X->V[0]=1; }
    X->counter = Ndim;  // set the counter to Ndim if iteration should happen right away
    X->sumtot = 1;
}


template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> void mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::seed_uniquestream( rng_state_t* Xin, uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID ){
    seed_vielbein(Xin,0);
    Xin->sumtot = apply_bigskip(Xin->V.data(), Xin->V.data(),  clusterID,  machineID,  runID,   streamID );
    Xin->counter = 1;
}


template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> boost::uint64_t mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::apply_bigskip( boost::uint64_t* Vout, boost::uint64_t* Vin, uint32_t clusterID, uint32_t machineID, uint32_t runID, uint32_t  streamID ){
    /*
     makes a derived state vector, Vout, from the mother state vector Vin
     by skipping a large number of steps, determined by the given seeding ID's
     
     it is mathematically guaranteed that the substreams derived in this way from the SAME (!!!) Vin will not collide provided
     1) at least one bit of ID is different
     2) less than 10^100 numbers are drawn from the stream
     (this is good enough : a single CPU will not exceed this in the lifetime of the universe, 10^19 sec,
     even if it had a clock cycle of Planck time, 10^44 Hz )
     
     Caution: never apply this to a derived vector, just choose some mother vector Vin, for example the unit vector by seed_vielbein(X,0),
     and use it in all your runs, just change runID to get completely nonoverlapping streams of random numbers on a different day.
     
     clusterID and machineID are provided for the benefit of large organizations who wish to ensure that a simulation
     which is running in parallel on a large number of  clusters and machines will have non-colliding source of random numbers.
     
     did i repeat it enough times? the non-collision guarantee is absolute, not probabilistic
     
     */
    
    
    const    boost::uint64_t skipMat17[128][17] =
#include "boost/random/detail/mixmax_skip_N17.ipp"
    ;
    
    const boost::uint64_t* skipMat[128];
    BOOST_ASSERT(Ndim==17);
    for (int i=0; i<128; i++) { skipMat[i] = skipMat17[i];}
    
    uint32_t IDvec[4] = {streamID, runID, machineID, clusterID};
    boost::uint64_t Y[Ndim], cum[Ndim];
    boost::uint64_t sumtot=0;
    
    for (int i=0; i<Ndim; i++) { Y[i] = Vin[i]; sumtot = modadd( sumtot, Vin[i]); } ;
    for (int IDindex=0; IDindex<4; IDindex++) { // go from lower order to higher order ID
        uint32_t id=IDvec[IDindex];
        int r = 0;
        while (id){
            if (id & 1) {
                boost::uint64_t* rowPtr = (boost::uint64_t*)skipMat[r + IDindex*8*sizeof(uint32_t)];
                for (int i=0; i<Ndim; i++){ cum[i] = 0; }
                for (int j=0; j<Ndim; j++){              // j is lag, enumerates terms of the poly
                    // for zero lag Y is already given
                    boost::uint64_t coeff = rowPtr[j]; // same coeff for all i
                    for (int i =0; i<Ndim; i++){
                        cum[i] =  fmodmulM61( cum[i], coeff ,  Y[i] ) ;
                    }
                    sumtot = iterate_raw_vec(Y, sumtot);
                }
                sumtot=0;
                for (int i=0; i<Ndim; i++){ Y[i] = cum[i]; sumtot = modadd( sumtot, cum[i]); } ;
            }
            id = (id >> 1); r++; // bring up the r-th bit in the ID
        }
    }
    sumtot=0;
    for (int i=0; i<Ndim; i++){ Vout[i] = Y[i]; sumtot = modadd( sumtot, Y[i]); } ;  // returns sumtot, and copy the vector over to Vout
    return (sumtot) ;
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> inline boost::uint64_t mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::fmodmulM61(boost::uint64_t cum, boost::uint64_t s, boost::uint64_t a){
    // works on all platforms, including 32-bit linux, PPC and PPC64, ARM and Windows
    const boost::uint64_t MASK32=0xFFFFFFFFULL;
    boost::uint64_t o,ph,pl,ah,al;
    o=(s)*a;
    ph = ((s)>>32);
    pl = (s) & MASK32;
    ah = a>>32;
    al = a & MASK32;
    o = (o & M61) + ((ph*ah)<<3) + ((ah*pl+al*ph + ((al*pl)>>32))>>29) ;
    o += cum;
    o = (o & M61) + ((o>>61));
    return o;
}

template <int Ndim, unsigned int SPECIALMUL, boost::int64_t SPECIAL> boost::uint64_t mixmax_engine  <Ndim, SPECIALMUL, SPECIAL> ::modadd(boost::uint64_t foo, boost::uint64_t bar){
    return MOD_MERSENNE(foo+bar);
}

/* @copydoc boost::random::detail::mixmax_engine_doc */
/** Instantiation with a valid parameter set. */
typedef mixmax_engine<17,36,0>          mixmax;
}// namespace random
}// namespace boost

#endif // BOOST_RANDOM_MIXMAX_HPP

/* mixmax.hpp
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
*/