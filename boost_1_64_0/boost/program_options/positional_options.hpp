// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02
#define BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02

#include <boost/program_options/config.hpp>

#include <vector>
#include <string>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::positional_options_description'
#endif

namespace boost { namespace program_options {

    /** Describes positional options. 

        The class allows to guess option names for positional options, which
        are specified on the command line and are identified by the position.
        The class uses the information provided by the user to associate a name
        with every positional option, or tell that no name is known. 

        The primary assumption is that only the relative order of the
        positional options themselves matters, and that any interleaving
        ordinary options don't affect interpretation of positional options.
        
        The user initializes the class by specifying that first N positional 
        options should be given the name X1, following M options should be given 
        the name X2 and so on. 
    */
    class BOOST_PROGRAM_OPTIONS_DECL positional_options_description {
    public:
        positional_options_description();

        /** Species that up to 'max_count' next positional options
            should be given the 'name'. The value of '-1' means 'unlimited'. 
            No calls to 'add' can be made after call with 'max_value' equal to 
            '-1'.            
        */
        positional_options_description&
        add(const char* name, int max_count);

        /** Returns the maximum number of positional options that can
            be present. Can return (numeric_limits<unsigned>::max)() to
            indicate unlimited number. */
        unsigned max_total_count() const;

        /** Returns the name that should be associated with positional
            options at 'position'. 
            Precondition: position < max_total_count()
        */
        const std::string& name_for_position(unsigned position) const;

    private:
        // List of names corresponding to the positions. If the number of
        // positions is unlimited, then the last name is stored in
        // m_trailing;
        std::vector<std::string> m_names;
        std::string m_trailing;
    };

}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif


/* positional_options.hpp
fz4L/YThmnwv8b+1vG+1CcU58A0PHmD9hv8+IFEuJtOZat4vKf22Tozm/nPYd/ab9FvE8+bEvwn82Ybt/GpJrmNkJ7Xum9Q/D+0Wa1/ozIUNad0H++4a7K0jGQHZ7+D1/wXUzU7yHdJzgfsf7OGxmmwTKS+bU8eAKJ/7/0Vo2w/V5kvbTuvABNid9rHfHu/uam7siCea453dia74dtvH25vjwt/C/t9L3q+H9rV+S7wZU0G6Ldj/Az9bi4+VSGtf2Oxl1E7W5G+tthZRG9yLb5jD/g0tXY3uDQXx2BXxN3sFed997Hwt34D64EHwH6/B19ybqQ1aXkWsuMY3bDmk0wd8/w/8k2vxXbxsXov7/zXcN93byjal/e5KrHZH5ibwH434pvIaQ7z+vw6NBL8fbmxMB44+OuyrwD63aGPj6CNc10bsqW94vz7dzsbRR5bN+s9gbz5sYSu8pU7ju+5N79cXhW0OHT2kaxiJPw7+FVa+/tpW9xZiXNZ25+1NbW07G/zrbPYr+Rcb0rn3bdyVOiDEtrjaGnUo/P4LvuOq2t+hwp3/HWjv1OSuJ8rdhMY8uG3WMWd3caXHAOv/vgvN4X1t38Iurig7Rv0Odm8NNma/+NqzLs399xD32a8Gf+v/Yf7jGw7fJ/wNcO8UfBtiL/w+6r+sbLhVwrFtmnvHg/3jYJgNt0q4vfn+7wfQkiiHuAr6S3z/F8wT/Wu82dLxXrNLl373k+z9EexbOIfQtHXL5rGOxs7GbRLC951Z//ZD7GkWpmb95rvgnvsfNw5DxWvZidn9EXzGMFNBq4CYj4J5hY9JPSqdCyVmw8fwEyNM+Ro/rn8G84JDwcStFhLkS+QqA9L9SmO4/hPEIccsbE39C3A3PIC4HfH2KreSy8Qq5d71lbh1nyIHYOMmS+I1JMQ9HdwNCyGuOVVnUwVxv5+4Uz6DtkvZxk2KrxfEPRzcxSP27qny9h9xp/kc9yWGotxSf6ZXet0g7hC4a1vsLVRK/dLtzPrv4K5u4+YLKrlr1j/8ArWGFnauohOz/xDMZWxMZ2/DzYrXRVMf7/ol6vuibJV2Ju6L4LaMRLlpJ+to1WR1fIU7XfuHuEZBBsJcalqPj4I9OBhi9ztDZumK9VR6Rbmsf/c1dA32i3KN9FsxlsmJr5n8/g/Y6fD4SmfUxlb9N4gNhJmprJNU0ODm/R/c1cP7sNmDY2Yv1uLWfQt/J2xv25bVLbE/WeoX5fL5F9zL9o9yi45RInEGxduaxtWU77xfnxpli2um8v4P5gVRpso7T7z/f+/9+uwoV3WNHgL32GHiNruPNOTSRmhZ4T4Hcb8F92Q7Vzx3EgO38ANypvv7uaTczxI7ajV7X4L/+HBtvlauNvsjcqVWNrTOkqVMSphPtn8K/kzWtnfLtMXfiyPb+3/C21oR2/+7e2eavijNZ/8P/DejfHMnLq367s+uP6N2K8Teq+KUXFFgYV1Yfv8G3B+t3HzOMX+6rS/c5sTf9Re8ATMZP5WvSOvWsP3g32Dlm+t6a7oy/uJrO+t//4q8TS1+vfzbBXz/E+z3S362e7snUSnqaEBv+Rs0Wf32+saZMVf8bUiaY/eC/amfbXiJTKlUqWpuDxRUuOv/jp/vH+TC3lyv8D5KbX0TuNkAN1XMVsPlJVesTlwXld9/+QO+8HCAnS/sozufLgP3fT8XIkKuTF+mrBYPq/sTueAoW+UtEI7/gTse4Lqi4uW8wnyitp7/L+Qe9w9z9Xw01r8B+5KIzcZgRZ94hr+hqxmw2fXIvPu3wnlW4g6DO6+Fa7wD8Vg69fGv4M5h4bq7o9vTsrnVdcnmf6BZHmB3tbZv0RZ331ZyP8AZMl0ek94=
*/