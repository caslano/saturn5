
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_RESULT_TYPE_HPP_INCLUDED
#define BOOST_FT_RESULT_TYPE_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/mpl/at.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T > struct result_type;

    namespace detail
    {
      template<typename T> struct result_type_impl
        : mpl::at_c
          < typename function_types::components<T>::types, 0 >
      { };
    }

    template<typename T> struct result_type
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , detail::result_type_impl<T>, boost::blank
        >::type
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,result_type,(T)) 
    };
  }
}

#endif


/* result_type.hpp
cAAxSquY6T4Jb7asYfKMBXj0t0A63LnBzewj8zMOIkStIzsubrpvT+Lw8dtkHrRSYLztCxzJ2Ma4oMn4PmMbk5/P4qNJp+Sd+FionL4vezAHYyfZizirJcweAGauKuU4jTx8fLmImtVdoFRpTn+lZNFFO5FrX98XeqduQjV+AOJGZrFbly7YGPsJDSsW0eyjH0f57sTUXDW07eMl56nGQydvKbUevKDussWyZbU3dN1KZF2gB0efGYWt3/egxTE7Bk0+Rsd54SgfHo7WegmYcVZgdfpv2IzZgvHvG5l7Ywyius0SeqnDaZv/nnCezKDeX4ThuJlsSDzC5ik6+HzaQTokNSJrgi3fLxuMhd2fwTzDm4M+t8bZpN/UWLmDH6/2w+1YR/lrcRFu2TnjruNCLvvWRhptrIGjWMzBEc3wYMMG7lZ+hbZxTT2khioe+buBy/aH82rbh+hmdgZFh1rLN5v1mF1OMWKsLR1uuUjvBhX0WrpAdMndDc3ctrKTwVCm71/D5wM/QKdPjDz9bAAtNJx5tbA1f/ns4Lj/DDBFebacGXoairHaosyjFD/U5ovOhvloWazMXTUjodzkE+uu3WLBrQksb7cH4r+73Hl+CMeMXiZUzxYyN9FY2E3exqvbQnFJpTMjUo2oVHqS617WcvK0Shz9tkuYjK2EZcNL0T/1MHs98kJ4RCNsF68Ug6y3sbaJIzoeqqCJQz/aRbxpcohtRa8h/3iigzcdlvejr+pzkbb2KUtfB0q7pV8Z46FB7TgP2n99y3Gf18CzQ61UquyCXtdayma3fuJVtJHsb2rJ+K+e8EvbyG97cjlioyHeBOXJmTlN7kgjTL7SXcHAh6fxqMnhNTsG6Dhn8La+FVY2BzzPKEn7V8F8NC6BBzJL8KCxJROX+OHxLQ8YZTbHLF09qbVkL5VXZFG1awX/TUwXFz28sUfBR6yatgcdou+JBUP+wahCXQxv/wWDtW7wa34Qmjnnyexv92mSdJrhAz8hs8iQCsXK2Dk8Wc75kouK3D7QNzRg3Kp5VNJ7SfOEbvCMrYPvantusjHFmbBHsG1bA/UeZeLSqnAGnSuX/w4Hcd+HgbD81ILrl26Uc+v200MnSj5VsIfFPnOUqcZyxNt6mfzMHrPDS+SE8HQ4PHOXqp0T8Cm9L26sD2VDWy8u9XBAw6RzuK1RTE2Fh+KDQxkOR9yXK8+p40/TDEveoMxkuUSOaD4WAYWXcc05Ano+GnLrrXrsvfhIhlwbzvDPlxC+eC4H+e8VvZ8ewu35/eXsdgEsuGCNF2fDoNq2D3o9XUSb9vXintpXFqWXQ//ERXr6urDK/QtmmCyQE+rbUOuClejga4F3G2J5eZwW5ybWYaCVJzeGzWXZZ3v8LNCUEwZ94ZvLWmj9pxWXDFnA74+XcFX5edEz7QEz6yy5Xu06tlveZ6TCAfqMdsNYd3/mD+8gWu62w+ztNQwxcsPZrpdxSV8TnsPP4D+zF+wpVgjTAZZIU4hhZmQTJwvsK2+u7Uuzta2F88nXHPDorbj08zR/NfGMNXeBFg6P5abAFARU1TEypoi2Oh1l6LfbUFS8AxdRgu59lYCQ0fw46Znsu30Bp7/KE+7aNlRucYc/k8x46+xgkRIRwVU3d8mACz2hMOWffKHdDne6agpOiKRHkC8eOdRj544xsq9lSxxe8w4nrfxxZ+EM+po40kx5oAi/dBSDI25BlX3RZlhPYTrKlZ6Z00SUfS1CdcNEglIDHj01kCs2T0fZ5flIbPUXPRNN0f98D6xZaE3fO7t4PSFLvvI0Rpr/S9QfM4ThZQc+ULSnsV6c3HrkEUdVeMDw+Tw2IkYo2l7DvpBBwnH9L8zJOC8=
*/