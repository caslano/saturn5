// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#include <boost/serialization/array.hpp>

#ifndef BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal input archive, which forwards reading to another archive
///
/// This class template is designed to use the loading facilities of another
/// input archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_iprimitive
{
public:

    /// the type of the archive to which the loading of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;

    /// the constructor takes a reference to the implementation archive used for loading primitve types
    forward_iprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    /// binary loading is forwarded to the implementation archive
    void load_binary(void * address, std::size_t count )
    {
      implementation_archive.load_binary(address,count);
    }
    
    /// loading of arrays is forwarded to the implementation archive
    template<class T>
    void load_array(serialization::array_wrapper<T> & x, unsigned int file_version )
    {
      implementation_archive.load_array(x,file_version);
    }

    typedef typename ImplementationArchive::use_array_optimization use_array_optimization;    

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::load_access;
protected:
#else
public:
#endif

    ///  loading of primitives is forwarded to the implementation archive
    template<class T>
    void load(T & t)
    {
      implementation_archive >> t;
    }

private:
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP

/* forward_iprimitive.hpp
eaIy5dtp1CPemPeNlI0Z076ADoziHT4WUO6CkfLGiX3+AeNMLRkn2FefxOmnEywSwaJ4kIotYZCwzmyreGSq2Cp2U0HJ3+MUfu4KtmsxP5BN/MBAqRDt/xL4Xtla9vNUtFrbo+DzlKzFyfLsFupNCrS8z7OMkrwoT1fstiDMQpPXT7YpkyGyzoFXj2F9QdKEqr8sW6nlp9GZJGzNID3wcfyuBvHZ++kHpDGO1G64hlKDlk6sttuVFUEmXFijUqrRptk7hFH1I0mlJrdyKmyHZuezpR9TntcdGfEin6l7nwS/UYrmP49oxAT4ytNXBpsHEvHQOUkSwyghWN4K6UsRvJmTygYpyLWiwIeY9DQkEf+dSlQIk+7npIbCVCJGkETqWdTetvGM/7Q6R0SIR9h5BYkjZuPGpaJ7esramaYRT0tSNb2Pt0IKRHWH0JH+uxwCrghqIJ2evVHFu/ZUaeiHMsK1/L8DB+unHcj6oGcLetIJcDJNVS/ECbPI8LOV6vzyxlKWAkSUoLv5E8yy/4X2G22kycYpKcINH6fewbsR4zesIdAed9qyYa7CbGKhAFV6gjJWLW4vv76Knw1X5Mj9eDp0kDVTAz3987nYEik23Sw2GIuxgG2ylpPvLewV8fyDK0ycxNcHNCY/AO1KhrZYoLUxoX0g2n2IDeBEBzYtbpozMnMmDVx80lVt5XtGzqTspT39hQwoIIC2jxRAt+MUde1t9+56DZM5oAuZvUhMTWRwVHeqQtRghsioKectJpiUcyrkgKYjj2YgH5xLpkXY/XQj1SPu0Dzp0EncIYJ3Rm7LvYt//x9L/j8h0n+ZBqjB23oqsTla8dWAKhohjy+BMnISkaTUUOyxakBZUIlwwV/4NIrfqyl0UjXoXFIJzbQC+HS4XUO+eq3bodRgY08cpbKN++MolWUsj6NUhjEtjlKaMTiOUl4juclS0VYA1WgFUE3vAOgOu3TSsB1fRekxIxCfmzOjrQAgR6OJd/PEw6IMqJhSJmrcgamK0NCqlUA1Xt6EwnS+psE1ie6lGRhWeTjhtiY7lejvkAgI6HKRcjOlYhZUxJOBsvsQr1tDQzF2GJqjhrgB6rfOSuKGLfnNQzbV8USA6E8sE8Xxe86x9+lRvvBBdys5e2VE9o0JVp80MrKIPb19mpxevxvg8KxkShN0ugymPdInIdAbtgKamNJCZ6lgKFOkqHUQ8RtV+YRjfqP6T/qgvWJ7vfaTTE0f+2A3zeg2sVF8S2PDaRH6QPBgeOlD3TT2LSov9kQ800Uy5KT/MDYqvsah1nIi+91EsB+3bF+7sI1MX9H02e3GAzQel71W/IMxUe0tstpLpPbGRbfnPcr2vKT/A+3RQ+PZja34WbCXYNrwo82bpfw1lzIAKUvOtp4PoVOIma1Dz7WMSRJ5RfHE5uUVHXNjyyNal08y4GV8Inxxw5f5+OUU+OKCL9n4ZSB8SYQvG/FLT/jigS/l+KU9fEnCYlX0tL4R/mna/8zCBA1KRN//Ryt9wUohVYkFPpuudGJeBvt/A43zYK6hPMJJCqhQp+QaTulajPQMx3Q4H5wgVzulazHSM6LS8Y25svgw2A/Sc37aDR3dFMDcm7YOA4iS3oSXmCsvnUBeSkHF1ZS8Gqd0LUZ6hmM6qC06Qa51StdipGdEpVcd4Y4n5lZCYBWRwGKZGjPWJHlJPwQCmdZp171A2YdAT+OW9GRSyzkcAZ5hS6LVF6d0r2M6JzpBrpHE6PlrDNkxXRJrhpKvwnIP4yMkBKem7gfhz1Bc7tpnPaLBX4vpfhfSyzKU8OgNXyAhes6jTrozk/bDcQ1f+Xib0HE/YEsVOusjTec1r9BkGXQKkpVUso0=
*/