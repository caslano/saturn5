//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#if(defined(__GNUC__) && __GNUC__ < 5)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>
namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into  boost::filesystem::path such all char strings are interpreted as utf-8 strings
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif

/* filesystem.hpp
TTo2zIW6kLk1y6acR7oHOUVxZk1LPjqHsURmgSn7tIHFkC3WLCttKD/s4weM68FOUcUs7em7qJKIb5hTVGQ25ZBPY8QQifLIlPYc4cR9/cy0of/m339EfGS7YPq5LmgkzWcw/XzmHkXnWTDlPIvsOUw5zxpN9YQp/WdgbgMLMbAwsp80y0Qb/H+YBHONcQpvk7SR/458iDlkLPIkU45VZG+1dH709/iXq6vksxxO0UtIK/DAT763NN4pSjB7EHLuMfYxsnlmaZ8mjZLvXU9yitws3cI+866hXcj8mV0rsjA7YifLxswvNsyJGMgsMOUdDrJ9JpbOHCK/nTBFH9/8zJsKox+mOkU+ZlsfFo1FeWSpLM9LDZYhvuTpThHA0mXe53mNMTHDiWckXLSh8aR+O1AeWROTtIGDRvVFnjPpfB7plPcmZjlFVpjy3gTZcC1PJ/39t+wiM9LNcYqNQlqz2Cy1UR5ZAWb/9i/QFzHEUAzMtre0lEcMZA2Z9RzYvAiOK2S8vH5xE0ahj+Y6xRhmQ6ve+hnlzXOKcswa5dl9Af1AVolZj4S8NTEGDcw13ylKM+t+aGg/jDOyXt7SNg6S10dJS5yiAUt3d2qOnxD7TzS3MptQfeSviI/MZJZmnd/3KuqyzCkCkU6/nkcIWX5m3XY/7orYyaJYnmtexzbBnPxz+nVJJAs3SZs8LPtdpFvJ6qKsO5JAxuuyK9zRH+OFrISXtOljqv0NW6vNrZqJz29jMCZ+ceJdfIfyLr5YR79lafHZTYKOI32GIt1GrS6a2W8ee4f4yAKZPalb+SDy3ETHRpO0y72byW8bb3aKQSxd170z16KPtjjxbpmNNixqGPke45PMymzxocKLsP+RWWD6eSmELBuz0X4+xTBf8zyV53cjFJsbnuiNGBS7lWl7YfStYg+7mOTzpkp8pXJ2e4s50iBdAjdl7dpEMhuz6GK/5sB+pKRr/O6aF8aLYpFT+sjvTG6lexfMLENPP0A/kBVilpogbNinybIwi+1URKA9lTwv3/zjNtpMsX+qJuRFu5CdYhYvWgvYNh6Dsp4AN+V9mUSydcw2ZGom1xOPZ+nUbzdzU97TSGCmjqXE+PTHZxJZCjORyV++t7vdKYbyNjsZuQR1IVttljbo7ELEIH7Tjqmata1skuu0kfH9oc8UxwD0HxnvvxwNfQqg/8jSiz2amdrWMUqek/YktUQMZOh3ZV3iRMWqRf7zG8YuL095LkjsZqY8F+RipsYQRFab2bLbe6IQH1kuZrd/m18XMfA8leeXEpipYymRm/IsVRI35VmqZG7Ks1Ti9/TjczFT+yiImdpmbmbquA7hpr7XQ1aT2bTbD+R6xmSZYfpnohK5Kc9EJXNTnt1y7WGmPLvl5qY8uxXGTXmWKoKb8lxXDDflOat4bsp7GonclOe6ksnSm8/EXqcoy+zsueTTiIEsvfnFQ7bW9M2sace/c0O2IL79TtFTSAs9vvAm6kJ2lVnrS+UDUJcDNL8w6+438iramuwks/sbZ8+FHXSKxswylGm3Au1JFsTs9JHc8tlsslzM3NU77EI9yYKZBTX4+hjlJThFSWZTp5qjEDtZZWZLvManojyyrDDlWXAyP5j+GkEcSj9dkIGFGJjnkHwOyUJ//bf5dEfsfzjFByEtf+Mt8n7PEacoyOzF1Uk9kSfZ98wOnr2VA8c/A0sysKCjdE3J7NHAFjcRn4F5yHIzC+9XVK4DYmAJZFmY5SrYexfqSZZTs++UdSTEMRq7MP06Em6yAJh+bQoPmQWmXNsfk+VlVMqLQXlkSnkJKI9MKS8Z5ZEp5Ynj8nw+A23Imq1VMOpJ1oJZ4MVm+zH3kDVhVrb9oVM=
*/