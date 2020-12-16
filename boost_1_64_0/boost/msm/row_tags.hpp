// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ROW_TAGS_H
#define BOOST_MSM_ROW_TAGS_H



namespace boost { namespace msm
{
//tags
struct a_row_tag {};
struct g_row_tag {};
struct _row_tag {};
struct row_tag {};
// tags for internal transitions
struct a_irow_tag {};
struct g_irow_tag {};
struct _irow_tag {};
struct irow_tag {};
// tags for transitions internal to state machines (not using any substate)
struct sm_a_i_row_tag {};
struct sm_g_i_row_tag {};
struct sm__i_row_tag {};
struct sm_i_row_tag {};

// flags used internally to handle terminate / interrupt states
struct TerminateFlag 
{
    typedef int non_forwarding_flag;
    typedef int event_blocking_flag;
};
struct InterruptedFlag
{
    typedef int non_forwarding_flag;
    typedef int event_blocking_flag;
};
template <class EndEvent>
struct EndInterruptFlag
{
    typedef int non_forwarding_flag;
};

} } // boost::msm
#endif //BOOST_MSM_ROW_TAGS_H


/* row_tags.hpp
zv3aaR/SvWeLmMsdY7ts3irvc7zg2C/rM4fSvGOA5jndScp6tXyMqs9O+yHnOWFOnE/TJ5erW+oAeWbeWTI/HSE3y+Y1qt3KfLFx6jgqPaKsX8m7v/iM2DqxSX32QscUq+aWx9T9DOc0N4r/v7XpWGPhbMd0I7Z9V0xbnK//V5/82xj3+WTpCO11jFO1b4jJvT7nf917E/JJ/e2nYmJV32of9HJlTMmPAXU7eItrOBtD7DrHAr53ntXGkr4KR6iL398Jn5F79o19168xNvTrR12ruUM/53Esm9Of1SV59yHxOcy4e6F2WjbXJEbda23vB87Bna9UniNnnWemvyzWjx9k2+b1dWKXMrcYnxnjLeNabNLxasn99DNi1eXaWvYsedgr19/g3Kp57frqzfLWsivG8pHy9eXKPFyc5GdodRz7rpjf3DzAd3eU2ZyH96ineSPp/Cs95NhT3lQpOQ6pyOMu5wkV17xyzbF1u3Jq6ieWGfWvPqKMHzlfM1aql8iFpxsjrslWDnMMkLPfbdiP7HJe5bXC4eYS93LJTNonGjtdrtF3/TW4TmafcJWcL5rzrhKjnfrD3JT9uON6eV36unngterd7LOfGRfuqVK+33z8LX36B33hM/PsvRv9pobrOOa1+k598LC2flR+aVPsKPlwtriYlyu2HTvXvN1vGecCXX+Sz4eLv5zral57d94ryCFzr3ZZJ7i2Ujdnd3/Revqwz9xdSNvP/I+9M/Fzsjjj+CCLgF0wnAJWjTdeGBZErFqDXK4KRA6ViiZ7ZJfIbhI2WQFta9qq1XrF+6ymKq1WLaFqrcUj3ige0V5erbHeVdvQerZW+53NvDPzvm8W/wH5fJbZvM/vnXnmuWfmfbOXsRfMPlxpT2wDbOxgfHWHEcyL+kfA66HY4t7M8zz0hi0Hf8h8SvKckpo3CP34AL5OLdeEbu5Gni/Ax5XYn6wFQoxxH3HpTvp9nHYa8qePUGQb4iY1yFR0dz86GoxvBcH+HNt7VNKxjaupq9njDVPzVm5m3uQ68QSy2IS+voWdvk8O2wW+fgxPxEv2QVjDYUepb6AfZDUFPWLTadpQA7b5BbHmzHHUnDIX0n9kFG3texYrHyGfzcSMNDmSc5oce6yRv1AHsTdT3BHfoKYM7o9O3oMn/C8/ihia4PeRtHnumYpu2TfI/WCseOIxfJwYXyBG5amlCudht8vZR9qIDzxM/FuJ7BsnsNanvw3Upl9gU6/C58vwJ/31Lq6vH82airgwhxi7llx6BfeORVa70id7UMV/otNH0QHn57l/EKPQa5p78sThMmsIMaSB/WpiCX6SY5++/GfWTfh9acIYIW5jPkNYIz1P/iB+5dYRZwus92+hfnqdePQmPycE2AcZS1/krOsZqxF+EuTBqcgXfZXeZA2/Evu4ClmfTx/4dIVz+eoFyGlffPcp8vBo8l8EnS1jHTAVOzmO3HUM9QJ6DqeJX/hpgfMNgdyCS+CRdUxsKX3dTM57GB99hxzLvILMtcr6OXImc9iAnFhTB1nX8KU5fBctvoJMcm8i45vGYfPEAHw8gGyD2EH1APQzDNyBjJUkN+FD6ZXEZmQXWk0fF/DDuqyMn4U4dy1GiMOC3PkBvr2RfI+uc/fh363sOd+Mntqp/0ZgZwLZ8jeufvo4uniVdabMXeehV+r68HHIq5V88Sn7BIdKmcLjY8SgS7jnC+IKa9sQcy7tRjy+jpj6JHF8Hjy/g21gF+Gp1I13MPaPkEMndiT3oScwxqfY8CvUU5zXl5fB17nj0Cl6x65iJ+HvBzBeFP4eouYIYHdp/O0OcvaO9PcucfEjYquMEewRhogFZfiNnY3e/sb8fkj8ew4=
*/