// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_WKT_HPP
#define BOOST_GEOMETRY_IO_WKT_WKT_HPP

#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>

// BSG 2011-02-03
// We don't include stream.hpp by default. That tries to stream anything not known
// by default (such as ttmath) and reports errors.
// Users can include stream.hpp themselves (if they want to)

#endif // BOOST_GEOMETRY_IO_WKT_WKT_HPP

/* wkt.hpp
W+FIuBJmwlVwGrwDLoBr4BK4Ae6Bm+AReA/8AD4I/w63wQTKsht2g0/CnnAvHASfgTkwiXzlwSI4BRbDDfBurj8CH4Q74AtwFzwEX4VH4EdwP/weHoVWxb8Jq8NjsAb8E+wK34Uj4Ak4Ef4F3gQ/gnfDj+G98BTcBT+Be+EZ+Ad4Fr4D/waNEMZPWAn+DGvBEPJ9LQyFY+EXuM+EX8L58Bt4Mwzn+hoYA9+CsfADWA1+BqvDqFC7XurCGrAhTIaXwtqwPWwIh8LG8DbYFK6Fl8IHYBv4MLTyexx2cNs6kjrDNNgF9oXd4AJ4GbwF9oabYV+4C/aDH8LB8FM4FH4Jr4A/wrHQ0mGUC5vDKTATXgWz4DWwEGZA6Z/yTZ28lO6fWufpfBgKF8JYeJM8v1fI+HSz9M9bYDO4VMbF5bCT+CM9Gj1G0uP7uErvFVnnNUSXRj34JuwF34aXw+OwAL4PS+BJuBH+BT4AT8E98Ct4HH4N34PfwL/Ab+G38Cw0TO4DrAV/hKnwJ3gx/BleAkNDuB8wHF4OI+BwGAVHwgpwJoyG22ES3AeT4X5YGx6EKfAoTIVvw7rwA9gY/gU2gZ+I/bTYv4VN4S+wGXRbus5gFEyDFeGlMB62hDVhB9gQdoTNYXfYFw6AQ+FQOBXeC2+Aj8EN8AC8B74I74MvwUfgy/AJeBDuga/AZ+Gr8AB8Db4Gj8A34FH4Z3gMnoZ/gvQ94x0YAY/DWPgeTIQnYC34PkyFp+EE+BXMg2fg7fBHuAn+BPdDMxQdI9AN/wZDYKTVz2FlGAarwghYC1aEl8BKsDOsBgfC6vBamAQnwnthIWwNj8L28DTsAL+FnaArlH4JG8AecBDsA6+CfWEG7AdnwoHwBjgIzoGXw9VwCFwPh8IH4TC4FV4JH4PD4bPwWvgSzIGH4ER4BE6C78Nc+BG8CZ6Gy+APcC2sGsbzDTaH62FHuAH2gnfBgXAjHAo3wavhZpgJH4BT4YNwLtwBV8CdcBN8HP4OPgGfgKO4L6/DTPguHAM/gBPgj3AyDGW8yYNRsADGwyKYAq+D3eH1sDecBYfAG+BIWAKvhnPgKDgXjoHz4AQ4H06BC+BUuBDOhovhUngLXAaXwJXwVrgaLoePwRVwD1wJX4IXwddgffgObABPwB7wC9gTfgOfhN/CPTA0gucojIKR1EscjIJV4Xe414Tfw4bwLGwKR1ntEmbA1nAk7AGvgn3hdLgAzoDr4Uy4DV4HH4PXwyfhLHgQzoavwxvhm7AEnoRz4CdwC4yMtNt5LNwL68J3YHN4HHaF78I+8AS8Er4PR8DX4Xh4GGbDP8Jp8AU4A66AJfA2OBfeDG+Gi+FSeAtcBZfAtXAr9XAXfAQ+BH8Ht8Ic+HuYDZ8R+xH4MeE+hKfgKXgH7i6eH2tgFFwLK8MpMAEOhNXgIFgbXg47wE88OoD1tyj1LY7nkH0G6yS0fk+JrLuDMBW+AuvBwab9fDuEvS18HXaDh2EPuT4IviUy0t6G8+FxuAj+Gd4GP4Tr4V/gE/Cv8Dn4BXwJfgXfg1/DT+D38DT8CcaQx7/DFPgLvASGm/bzKgIOhpFwBIyCo2AFOBpWhuNhDMyFsTAPxsFiGA/nwGpwBawOd8AkuAcmwwMwBb4CU+FRWA+egM3hKZgGv4ItYGXqty2Mh11gFdgT1ocNYRPYC6bB3rAFHADbwoGwK0yHg2FLWARbwWmwHZwF28PVsAO8C3aE98FOcBccDEXWoXy3oWyYbD9Zh5/Le/iXMByehlHwKxgt7tXgGWlHZz3fN+S7DfERF/FA9V5ulQuOha3gODgSZsEcmAOnw2J4J7we7oWz4B/gbPgSvBEehCXwCzgHfgc=
*/