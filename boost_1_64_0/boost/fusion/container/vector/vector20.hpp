/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR20_11052014_2316
#define FUSION_VECTOR20_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector20.hpp
45sZ10W4rrsw7k/oj1N3Ydx/T+XrNIz7T6q6ug7j/ooqXwfyTn1lfqv1hx8oKEn+D3t3Ah9FdQdwfCmHoBADQoAQIFwaATFowAgBAgQI9wIRAgQ2xyYkkGNJNiFAwADhviKCjRYwIiCXGiEgCLZYbYtWKyqttEVLFVva0pZWa2lrj9/s/HcyO5klu8Fij50P7/NlJ/PmvXlz7M68Yz77dFrGb6ddmB9bvzqQqxb5vS/3AWsoY/7E+AlMMu5MW2yEnbEx3oNNMAZvwfHYFGdiM0zFWzEbb0MnNsfF2AKXYxBuwNvxMWyJO/EO3IutsQrb4Clsi9/F9ngOQ6UfdhgOxY64FzvjsxiOL2IXPInd8DR218Z9kd/8ci+wxtB/erj0u47DcByBETgSh+MonITxmIlj8I94nnBR1pst5dmO/79p8RxfwIo9cBL2xsk4AKdgPCbgVHwIM3AqFuE0XIWJWIHTcR/OxBOYhGdxFl7A2fgx2vBPmCzjZ6RgH0zFAZiGg9GOVszAVJyDczBTtu9sA/n9L/cDyvY9wP9fk3vJeVJe2dgHc3Ad5uFWdOBOnI/7MR+PYCF+E4vwDC7Ac1iMH+Ji/BWW4Ke4BP+JS7EZaa/EtrgKu+AavAfX4gO4AUfgRpyIm3AmbsZ0fBTz8DEswq9jGX4Dt+AO3I47cT8+iUdwF76CT+P3cS9ewGfwF3gAf4sH8c94CBtTZs/i7ViFnfAFjMBqHI5HcRIew+n4ImbhCSzCl3AJvoyb8JtYga/gXvw2VuOreBK/i2/i9/A9fAPP41uyX89Y5H4Az8lxG8L/T8lx+4687+9d7IvnMBZ/iPPxfTkuz8t+/gk+jT/FF/ACnsQP8Hv4Ib6DF/EX+BH+CT/GO2XcloH4SxyDl7EYf40b8Yrsj9/iG/h7fBuvyvZkNpDfvPJbeA2hJ/9PkuN0sYyPsBTvwVIci8swD5djEZbhelyJu3EVHsbV+DKuwXO4Fj/E9fgX3IBK4huxGW7C9rgZu2E5RuAWHIBbcThuw3H4GNrx6zgPK7AIH8d1+ARuxe14AHfgC7gTT+CT+AZW4i/wKfwd7sJPcTcq43/swRa4F+fhPszB/bgMD+BaPIR78Fk8iFX4LL6AlDcbK7+TcbtcT1ugU46fSLme3o99MAr7Yz8cgP1xBD6AkzAaZ+GDmIED0YkxcpwNwi04BL+OsSj5kN/L5M0kH1nyfTYXw3Ee9sZstGIOJmAezkYHZuB8nIv5uAKd+AQW4k4swkO4QMqDePL7mN/Ncj714v92Of7ulnz0lHz0wj7YBx/EezEJ+0r692Em9sN87I9OfBCX4gAsxUG4DodIvmJxHw7HaozDb+II/C6OxLdwFF7AeDmOR+Mvcaxsz3hsQt4nYDBOxHZoxc44CfvgZIzGKRiLCTgKH8KZOBVTcTpm4wx04kxcikm4HGfjHkzG5zEFj2Eqvol2/BGm408wA/c15Lt22y2WqG23+NTmwjAOiX4MEm3ske6HvfZTMIw34nWsERlfxPf2GTKWiDZmyGfMq0DjOCHGthsXpf2GezyQcDSMAWLalmNf7fYc2ngfl2S8D0P7DhnfQxvbQ8b18P6OxVKCYewOk/Yf+jE6TMfnUNuEDPfWLsS/cTik/4SMv1HTZuTScGk3ImNt8H5Gv8fbuN5YG63vr3uMDV/6WzCOhk9jaJSje9yMBEKJu/0JwTg+xjW8hq3jje1RML6mTUpivH7cC88xL3aXMHYF4RLBsqSZJYwQQ0giFBMqlgTasASmwBSYAlNg+u+ebkL7f3f1/w3X/Rco7/6T9v+95T7kFUIruc/fqbT//6G0/3cla7MXOnyvZ+inPmvPzJF5kbija80=
*/