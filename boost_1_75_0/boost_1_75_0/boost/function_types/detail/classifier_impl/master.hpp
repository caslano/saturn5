
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#if BOOST_FT_ARITY_LOOP_PREFIX

#   ifndef BOOST_FT_DETAIL_CLASSIFIER_IMPL_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_CLASSIFIER_IMPL_MASTER_HPP_INCLUDED
#     include <boost/preprocessor/facilities/identity.hpp>
#   endif

#   define BOOST_FT_type_name

#elif BOOST_FT_ARITY_LOOP_IS_ITERATING

template< BOOST_FT_tplargs(BOOST_PP_IDENTITY(typename)) >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,BOOST_FT_arity>::type
classifier_impl(BOOST_FT_type);

#elif BOOST_FT_ARITY_LOOP_SUFFIX

#   undef BOOST_FT_type_name

#else
#   error "attempt to use arity loop master file without loop"
#endif


/* master.hpp
xC3kGde/TdyCGIEH35OjYQx9PDgC2Afv60c8jpU3PMc+fTiiITibIRGkSK6MBc5/ruNY4DB9Hi4AMSxzOYZqIYvrL42wNYAnN7yviQIh1msBzrVp1lQ8BF36eVdPNQp72NQERwPU/v4L2Dk8Faxb8yCqBUbEw63ZZlMS7qK5epIMn33WezYZeBXH4PVFJuosXNSoRWAD4VgLdAbZjDmFiLW/mJjjUltwLFZEqk6bJVK12UwUpwVf39rG+s9NdH1uWzjbFdo+Yhaep3hSjFUAAoNaNisv4bAZhQHnpHcEPkl94owFnZThGaDUWTGIUg+mIUrNuwJRqq5DotLnG4feNLNxBZznvJNgRlgwbI86bGaIY4p7jXFA36N9f5bkRFGfOAs50Y+JE31KMqBPS5Z0ruREn+FEg5UmM1Yp+U08UJYht4m6oALw/iGb3isXQkp4ODMB8cv3sJmrM4vNXPOM+34HFkEUqM9A0vjVQmA9DTE0PVy+HbRcXphNrOe5yHp+jsEaviF3cbGY/4ZTj29UcqFstveEo8XnuJa81oXOoHlGc2xjEB3cCowzd8GtgLP+IoCqJ7brepeoeG/qoyAYKAxl1i7qXWl5qnJKKn8gj3L3eZLdfejEQceJjFmdcFbThnehhxA3MKUdDPtqWGOc/OB5mfxgOxsIbzXKcsjA7dooqmAmVZS6qwtZyEXaTAs5cBGqtJlVbDXiB9LX
*/