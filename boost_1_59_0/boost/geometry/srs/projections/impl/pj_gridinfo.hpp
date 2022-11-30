// Boost.Geometry
// This file is manually converted from PROJ4

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// This file was converted to Geometry Library by Adam Wulkiewicz

// Original copyright notice:
// Author:   Frank Warmerdam, warmerdam@pobox.com

// Copyright (c) 2000, Frank Warmerdam

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDINFO_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDINFO_HPP


#include <boost/algorithm/string.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/cstdint.hpp>

#include <algorithm>
#include <string>
#include <vector>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

/************************************************************************/
/*                             swap_words()                             */
/*                                                                      */
/*      Convert the byte order of the given word(s) in place.           */
/************************************************************************/

inline bool is_lsb()
{
    static const int byte_order_test = 1;
    static bool result = (1 == ((const unsigned char *) (&byte_order_test))[0]);
    return result;
}

inline void swap_words( char *data, int word_size, int word_count )
{
    for (int word = 0; word < word_count; word++)
    {
        for (int i = 0; i < word_size/2; i++)
        {
            std::swap(data[i], data[word_size-i-1]);
        }

        data += word_size;
    }
}

inline bool cstr_equal(const char * s1, const char * s2, std::size_t n)
{
    return std::equal(s1, s1 + n, s2);
}

struct is_trimmable_char
{
    inline bool operator()(char ch)
    {
        return ch == '\n' || ch == ' ';
    }
};

// structs originally defined in projects.h

struct pj_ctable
{
    struct lp_t  { double lam, phi; };
    struct flp_t { float lam, phi; };
    struct ilp_t { boost::int32_t lam, phi; };

    std::string id;         // ascii info
    lp_t ll;                // lower left corner coordinates
    lp_t del;               // size of cells
    ilp_t lim;              // limits of conversion matrix
    std::vector<flp_t> cvs; // conversion matrix

    inline void swap(pj_ctable & r)
    {
        id.swap(r.id);
        std::swap(ll, r.ll);
        std::swap(del, r.del);
        std::swap(lim, r.lim);
        cvs.swap(r.cvs);
    }
};

struct pj_gi_load
{
    enum format_t { missing = 0, ntv1, ntv2, gtx, ctable, ctable2 };
    typedef boost::long_long_type offset_t;

    explicit pj_gi_load(std::string const& gname = "",
                        format_t f = missing,
                        offset_t off = 0,
                        bool swap = false)
        : gridname(gname)
        , format(f)
        , grid_offset(off)
        , must_swap(swap)
    {}

    std::string gridname; // identifying name of grid, eg "conus" or ntv2_0.gsb

    format_t format;      // format of this grid, ie "ctable", "ntv1", "ntv2" or "missing".

    offset_t grid_offset; // offset in file, for delayed loading
    bool must_swap;       // only for NTv2

    pj_ctable ct;

    inline void swap(pj_gi_load & r)
    {
        gridname.swap(r.gridname);
        std::swap(format, r.format);
        std::swap(grid_offset, r.grid_offset);
        std::swap(must_swap, r.must_swap);
        ct.swap(r.ct);
    }

};

struct pj_gi
    : pj_gi_load
{
    explicit pj_gi(std::string const& gname = "",
                   pj_gi_load::format_t f = missing,
                   pj_gi_load::offset_t off = 0,
                   bool swap = false)
        : pj_gi_load(gname, f, off, swap)
    {}

    std::vector<pj_gi> children;

    inline void swap(pj_gi & r)
    {
        pj_gi_load::swap(r);
        children.swap(r.children);
    }
};

typedef std::vector<pj_gi> pj_gridinfo;


/************************************************************************/
/*                   pj_gridinfo_load_ctable()                          */
/*                                                                      */
/*      Load the data portion of a ctable formatted grid.               */
/************************************************************************/

// Originally nad_ctable_load() defined in nad_init.c
template <typename IStream>
bool pj_gridinfo_load_ctable(IStream & is, pj_gi_load & gi)
{
    pj_ctable & ct = gi.ct;
    
    // Move the input stream by the size of the proj4 original CTABLE
    std::size_t header_size = 80
                            + 2 * sizeof(pj_ctable::lp_t)
                            + sizeof(pj_ctable::ilp_t)
                            + sizeof(pj_ctable::flp_t*);
    is.seekg(header_size);
    
    // read all the actual shift values
    std::size_t a_size = ct.lim.lam * ct.lim.phi;
    ct.cvs.resize(a_size);
    
    std::size_t ch_size = sizeof(pj_ctable::flp_t) * a_size;
    is.read(reinterpret_cast<char*>(&ct.cvs[0]), ch_size);

    if (is.fail() || std::size_t(is.gcount()) != ch_size)
    {
        ct.cvs.clear();
        //ctable loading failed on fread() - binary incompatible?
        return false;
    }

    return true;
} 

/************************************************************************/
/*                  pj_gridinfo_load_ctable2()                          */
/*                                                                      */
/*      Load the data portion of a ctable2 formatted grid.              */
/************************************************************************/

// Originally nad_ctable2_load() defined in nad_init.c
template <typename IStream>
bool pj_gridinfo_load_ctable2(IStream & is, pj_gi_load & gi)
{
    pj_ctable & ct = gi.ct;

    is.seekg(160);

    // read all the actual shift values
    std::size_t a_size = ct.lim.lam * ct.lim.phi;
    ct.cvs.resize(a_size);

    std::size_t ch_size = sizeof(pj_ctable::flp_t) * a_size;
    is.read(reinterpret_cast<char*>(&ct.cvs[0]), ch_size);

    if (is.fail() || std::size_t(is.gcount()) != ch_size)
    {
        //ctable2 loading failed on fread() - binary incompatible?
        ct.cvs.clear();
        return false;
    }

    if (! is_lsb())
    {
        swap_words(reinterpret_cast<char*>(&ct.cvs[0]), 4, (int)a_size * 2);
    }

    return true;
}

/************************************************************************/
/*                      pj_gridinfo_load_ntv1()                         */
/*                                                                      */
/*      NTv1 format.                                                    */
/*      We process one line at a time.  Note that the array storage     */
/*      direction (e-w) is different in the NTv1 file and what          */
/*      the CTABLE is supposed to have.  The phi/lam are also           */
/*      reversed, and we have to be aware of byte swapping.             */
/************************************************************************/

// originally in pj_gridinfo_load() function
template <typename IStream>
inline bool pj_gridinfo_load_ntv1(IStream & is, pj_gi_load & gi)
{
    static const double s2r = math::d2r<double>() / 3600.0;

    std::size_t const r_size = gi.ct.lim.lam * 2;
    std::size_t const ch_size = sizeof(double) * r_size;

    is.seekg(gi.grid_offset);

    std::vector<double> row_buf(r_size);
    gi.ct.cvs.resize(gi.ct.lim.lam * gi.ct.lim.phi);
    
    for (boost::int32_t row = 0; row < gi.ct.lim.phi; row++ )
    {
        is.read(reinterpret_cast<char*>(&row_buf[0]), ch_size);

        if (is.fail() || std::size_t(is.gcount()) != ch_size)
        {
            gi.ct.cvs.clear();
            return false;
        }

        if (is_lsb())
            swap_words(reinterpret_cast<char*>(&row_buf[0]), 8, (int)r_size);

        // convert seconds to radians
        for (boost::int32_t i = 0; i < gi.ct.lim.lam; i++ )
        {
            pj_ctable::flp_t & cvs = gi.ct.cvs[row * gi.ct.lim.lam + (gi.ct.lim.lam - i - 1)];

            cvs.phi = (float) (row_buf[i*2] * s2r);
            cvs.lam = (float) (row_buf[i*2+1] * s2r);
        }
    }

    return true;
}

/* -------------------------------------------------------------------- */
/*                         pj_gridinfo_load_ntv2()                      */
/*                                                                      */
/*      NTv2 format.                                                    */
/*      We process one line at a time.  Note that the array storage     */
/*      direction (e-w) is different in the NTv2 file and what          */
/*      the CTABLE is supposed to have.  The phi/lam are also           */
/*      reversed, and we have to be aware of byte swapping.             */
/* -------------------------------------------------------------------- */

// originally in pj_gridinfo_load() function
template <typename IStream>
inline bool pj_gridinfo_load_ntv2(IStream & is, pj_gi_load & gi)
{
    static const double s2r = math::d2r<double>() / 3600.0;

    std::size_t const r_size = gi.ct.lim.lam * 4;
    std::size_t const ch_size = sizeof(float) * r_size;

    is.seekg(gi.grid_offset);

    std::vector<float> row_buf(r_size);
    gi.ct.cvs.resize(gi.ct.lim.lam * gi.ct.lim.phi);

    for (boost::int32_t row = 0; row < gi.ct.lim.phi; row++ )
    {
        is.read(reinterpret_cast<char*>(&row_buf[0]), ch_size);

        if (is.fail() || std::size_t(is.gcount()) != ch_size)
        {
            gi.ct.cvs.clear();
            return false;
        }

        if (gi.must_swap)
        {
            swap_words(reinterpret_cast<char*>(&row_buf[0]), 4, (int)r_size);
        }

        // convert seconds to radians
        for (boost::int32_t i = 0; i < gi.ct.lim.lam; i++ )
        {
            pj_ctable::flp_t & cvs = gi.ct.cvs[row * gi.ct.lim.lam + (gi.ct.lim.lam - i - 1)];

            // skip accuracy values
            cvs.phi = (float) (row_buf[i*4] * s2r);
            cvs.lam = (float) (row_buf[i*4+1] * s2r);
        }
    }

    return true;
}

/************************************************************************/
/*                   pj_gridinfo_load_gtx()                             */
/*                                                                      */
/*      GTX format.                                                     */
/************************************************************************/

// originally in pj_gridinfo_load() function
template <typename IStream>
inline bool pj_gridinfo_load_gtx(IStream & is, pj_gi_load & gi)
{
    boost::int32_t words = gi.ct.lim.lam * gi.ct.lim.phi;
    std::size_t const ch_size = sizeof(float) * words;
    
    is.seekg(gi.grid_offset);

    // TODO: Consider changing this unintuitive code
    // NOTE: Vertical shift data (one float per point) is stored in a container
    // holding horizontal shift data (two floats per point).
    gi.ct.cvs.resize((words + 1) / 2);

    is.read(reinterpret_cast<char*>(&gi.ct.cvs[0]), ch_size);

    if (is.fail() || std::size_t(is.gcount()) != ch_size)
    {
        gi.ct.cvs.clear();
        return false;
    }

    if (is_lsb())
    {
        swap_words(reinterpret_cast<char*>(&gi.ct.cvs[0]), 4, words);
    }

    return true;
}

/************************************************************************/
/*                          pj_gridinfo_load()                          */
/*                                                                      */
/*      This function is intended to implement delayed loading of       */
/*      the data contents of a grid file.  The header and related       */
/*      stuff are loaded by pj_gridinfo_init().                         */
/************************************************************************/

template <typename IStream>
inline bool pj_gridinfo_load(IStream & is, pj_gi_load & gi)
{
    if (! gi.ct.cvs.empty())
    {
        return true;
    }

    if (! is.is_open())
    {
        return false;
    }

    // Original platform specific CTable format.
    if (gi.format == pj_gi::ctable)
    {
        return pj_gridinfo_load_ctable(is, gi);
    }
    // CTable2 format.
    else if (gi.format == pj_gi::ctable2)
    {
        return pj_gridinfo_load_ctable2(is, gi);
    }
    // NTv1 format.
    else if (gi.format == pj_gi::ntv1)
    {
        return pj_gridinfo_load_ntv1(is, gi);
    }
    // NTv2 format.
    else if (gi.format == pj_gi::ntv2)
    {
        return pj_gridinfo_load_ntv2(is, gi);
    }
    // GTX format.
    else if (gi.format == pj_gi::gtx)
    {
        return pj_gridinfo_load_gtx(is, gi);
    }
    else
    {
        return false;
    }
}

/************************************************************************/
/*                        pj_gridinfo_parent()                          */
/*                                                                      */
/*      Seek a parent grid file by name from a grid list                */
/************************************************************************/

template <typename It>
inline It pj_gridinfo_parent(It first, It last, std::string const& name)
{
    for ( ; first != last ; ++first)
    {
        if (first->ct.id == name)
            return first;

        It parent = pj_gridinfo_parent(first->children.begin(), first->children.end(), name);
        if( parent != first->children.end() )
            return parent;
    }

    return last;
}

/************************************************************************/
/*                       pj_gridinfo_init_ntv2()                        */
/*                                                                      */
/*      Load a ntv2 (.gsb) file.                                        */
/************************************************************************/

template <typename IStream>
inline bool pj_gridinfo_init_ntv2(std::string const& gridname,
                                  IStream & is,
                                  pj_gridinfo & gridinfo)
{
    BOOST_STATIC_ASSERT( sizeof(boost::int32_t) == 4 );
    BOOST_STATIC_ASSERT( sizeof(double) == 8 );

    static const double s2r = math::d2r<double>() / 3600.0;

    std::size_t gridinfo_orig_size = gridinfo.size();

    // Read the overview header.
    char header[11*16];

    is.read(header, sizeof(header));
    if( is.fail() )
    {
        return false;
    }

    bool must_swap = (header[8] == 11)
                   ? !is_lsb()
                   : is_lsb();

    // NOTE: This check is not implemented in proj4
    if (! cstr_equal(header + 56, "SECONDS", 7))
    {
        return false;
    }

    // Byte swap interesting fields if needed.
    if( must_swap )
    {
        swap_words( header+8, 4, 1 );
        swap_words( header+8+16, 4, 1 );
        swap_words( header+8+32, 4, 1 );
        swap_words( header+8+7*16, 8, 1 );
        swap_words( header+8+8*16, 8, 1 );
        swap_words( header+8+9*16, 8, 1 );
        swap_words( header+8+10*16, 8, 1 );
    }

    // Get the subfile count out ... all we really use for now.
    boost::int32_t num_subfiles;
    memcpy( &num_subfiles, header+8+32, 4 );

    // Step through the subfiles, creating a PJ_GRIDINFO for each.
    for( boost::int32_t subfile = 0; subfile < num_subfiles; subfile++ )
    {
        // Read header.
        is.read(header, sizeof(header));
        if( is.fail() )
        {
            return false;
        }

        if(! cstr_equal(header, "SUB_NAME", 8))
        {
            return false;
        }

        // Byte swap interesting fields if needed.
        if( must_swap )
        {
            swap_words( header+8+16*4, 8, 1 );
            swap_words( header+8+16*5, 8, 1 );
            swap_words( header+8+16*6, 8, 1 );
            swap_words( header+8+16*7, 8, 1 );
            swap_words( header+8+16*8, 8, 1 );
            swap_words( header+8+16*9, 8, 1 );
            swap_words( header+8+16*10, 4, 1 );
        }

        // Initialize a corresponding "ct" structure.
        pj_ctable ct;
        pj_ctable::lp_t ur;

        ct.id = std::string(header + 8, 8);

        ct.ll.lam = - *((double *) (header+7*16+8)); /* W_LONG */
        ct.ll.phi = *((double *) (header+4*16+8));   /* S_LAT */

        ur.lam = - *((double *) (header+6*16+8));     /* E_LONG */
        ur.phi = *((double *) (header+5*16+8));       /* N_LAT */

        ct.del.lam = *((double *) (header+9*16+8));
        ct.del.phi = *((double *) (header+8*16+8));

        ct.lim.lam = (boost::int32_t) (fabs(ur.lam-ct.ll.lam)/ct.del.lam + 0.5) + 1;
        ct.lim.phi = (boost::int32_t) (fabs(ur.phi-ct.ll.phi)/ct.del.phi + 0.5) + 1;

        ct.ll.lam *= s2r;
        ct.ll.phi *= s2r;
        ct.del.lam *= s2r;
        ct.del.phi *= s2r;

        boost::int32_t gs_count;
        memcpy( &gs_count, header + 8 + 16*10, 4 );
        if( gs_count != ct.lim.lam * ct.lim.phi )
        {
            return false;
        }

        //ct.cvs.clear();

        // Create a new gridinfo for this if we aren't processing the
        // 1st subfile, and initialize our grid info.

        // Attach to the correct list or sublist.

        // TODO is offset needed?
        pj_gi gi(gridname, pj_gi::ntv2, is.tellg(), must_swap);
        gi.ct = ct;

        if( subfile == 0 )
        {
            gridinfo.push_back(gi);
        }
        else if( cstr_equal(header+24, "NONE", 4) )
        {
            gridinfo.push_back(gi);
        }
        else
        {
            pj_gridinfo::iterator git = pj_gridinfo_parent(gridinfo.begin() + gridinfo_orig_size,
                                                           gridinfo.end(),
                                                           std::string((const char*)header+24, 8));

            if( git == gridinfo.end() )
            {
                gridinfo.push_back(gi);
            }
            else
            {
                git->children.push_back(gi);
            }
        }

        // Seek past the data.
        is.seekg(gs_count * 16, std::ios::cur);
    }

    return true;
}

/************************************************************************/
/*                       pj_gridinfo_init_ntv1()                        */
/*                                                                      */
/*      Load an NTv1 style Canadian grid shift file.                    */
/************************************************************************/

template <typename IStream>
inline bool pj_gridinfo_init_ntv1(std::string const& gridname,
                                  IStream & is,
                                  pj_gridinfo & gridinfo)
{
    BOOST_STATIC_ASSERT( sizeof(boost::int32_t) == 4 );
    BOOST_STATIC_ASSERT( sizeof(double) == 8 );

    static const double d2r = math::d2r<double>();

    // Read the header.
    char header[176];

    is.read(header, sizeof(header));
    if( is.fail() )
    {
        return false;
    }

    // Regularize fields of interest.
    if( is_lsb() )
    {
        swap_words( header+8, 4, 1 );
        swap_words( header+24, 8, 1 );
        swap_words( header+40, 8, 1 );
        swap_words( header+56, 8, 1 );
        swap_words( header+72, 8, 1 );
        swap_words( header+88, 8, 1 );
        swap_words( header+104, 8, 1 );
    }

    // NTv1 grid shift file has wrong record count, corrupt?
    if( *((boost::int32_t *) (header+8)) != 12 )
    {
        return false;
    }

    // NOTE: This check is not implemented in proj4
    if (! cstr_equal(header + 120, "SECONDS", 7))
    {
        return false;
    }

    // Fill in CTABLE structure.
    pj_ctable ct;
    pj_ctable::lp_t ur;

    ct.id = "NTv1 Grid Shift File";

    ct.ll.lam = - *((double *) (header+72));
    ct.ll.phi = *((double *) (header+24));
    ur.lam = - *((double *) (header+56));
    ur.phi = *((double *) (header+40));
    ct.del.lam = *((double *) (header+104));
    ct.del.phi = *((double *) (header+88));
    ct.lim.lam = (boost::int32_t) (fabs(ur.lam-ct.ll.lam)/ct.del.lam + 0.5) + 1;
    ct.lim.phi = (boost::int32_t) (fabs(ur.phi-ct.ll.phi)/ct.del.phi + 0.5) + 1;

    ct.ll.lam *= d2r;
    ct.ll.phi *= d2r;
    ct.del.lam *= d2r;
    ct.del.phi *= d2r;
    //ct.cvs.clear();

    // is offset needed?
    gridinfo.push_back(pj_gi(gridname, pj_gi::ntv1, is.tellg()));
    gridinfo.back().ct = ct;

    return true;
}

/************************************************************************/
/*                       pj_gridinfo_init_gtx()                         */
/*                                                                      */
/*      Load a NOAA .gtx vertical datum shift file.                     */
/************************************************************************/

template <typename IStream>
inline bool pj_gridinfo_init_gtx(std::string const& gridname,
                                 IStream & is,
                                 pj_gridinfo & gridinfo)
{
    BOOST_STATIC_ASSERT( sizeof(boost::int32_t) == 4 );
    BOOST_STATIC_ASSERT( sizeof(double) == 8 );

    static const double d2r = math::d2r<double>();

    // Read the header.
    char header[40];

    is.read(header, sizeof(header));
    if( is.fail() )
    {
        return false;
    }

    // Regularize fields of interest and extract.
    double         xorigin, yorigin, xstep, ystep;
    boost::int32_t rows, columns;

    if( is_lsb() )
    {
        swap_words( header+0, 8, 4 );
        swap_words( header+32, 4, 2 );
    }

    memcpy( &yorigin, header+0, 8 );
    memcpy( &xorigin, header+8, 8 );
    memcpy( &ystep, header+16, 8 );
    memcpy( &xstep, header+24, 8 );

    memcpy( &rows, header+32, 4 );
    memcpy( &columns, header+36, 4 );

    // gtx file header has invalid extents, corrupt?
    if( xorigin < -360 || xorigin > 360
        || yorigin < -90 || yorigin > 90 )
    {
        return false;
    }

    // Fill in CTABLE structure.
    pj_ctable ct;

    ct.id = "GTX Vertical Grid Shift File";

    ct.ll.lam = xorigin;
    ct.ll.phi = yorigin;
    ct.del.lam = xstep;
    ct.del.phi = ystep;
    ct.lim.lam = columns;
    ct.lim.phi = rows;

    // some GTX files come in 0-360 and we shift them back into the
    // expected -180 to 180 range if possible. This does not solve
    // problems with grids spanning the dateline.
    if( ct.ll.lam >= 180.0 )
        ct.ll.lam -= 360.0;

    if( ct.ll.lam >= 0.0 && ct.ll.lam + ct.del.lam * ct.lim.lam > 180.0 )
    {
        //"This GTX spans the dateline!  This will cause problems." );
    }

    ct.ll.lam *= d2r;
    ct.ll.phi *= d2r;
    ct.del.lam *= d2r;
    ct.del.phi *= d2r;
    //ct.cvs.clear();

    // is offset needed?
    gridinfo.push_back(pj_gi(gridname, pj_gi::gtx, 40));
    gridinfo.back().ct = ct;

    return true;
}

/************************************************************************/
/*                   pj_gridinfo_init_ctable2()                         */
/*                                                                      */
/*      Read the header portion of a "ctable2" format grid.             */
/************************************************************************/

// Originally nad_ctable2_init() defined in nad_init.c
template <typename IStream>
inline bool pj_gridinfo_init_ctable2(std::string const& gridname,
                                     IStream & is,
                                     pj_gridinfo & gridinfo)
{
    BOOST_STATIC_ASSERT( sizeof(boost::int32_t) == 4 );
    BOOST_STATIC_ASSERT( sizeof(double) == 8 );

    char header[160];

    is.read(header, sizeof(header));
    if( is.fail() )
    {
        return false;
    }

    if( !is_lsb() )
    {
        swap_words( header +  96, 8, 4 );
        swap_words( header + 128, 4, 2 );
    }

    // ctable2 - wrong header!
    if (! cstr_equal(header, "CTABLE V2", 9))
    {
        return false;
    }

    // read the table header
    pj_ctable ct;

    ct.id = std::string(header + 16, std::find(header + 16, header + 16 + 80, '\0'));
    //memcpy( &ct.ll.lam,  header +  96, 8 );
    //memcpy( &ct.ll.phi,  header + 104, 8 );
    //memcpy( &ct.del.lam, header + 112, 8 );
    //memcpy( &ct.del.phi, header + 120, 8 );
    //memcpy( &ct.lim.lam, header + 128, 4 );
    //memcpy( &ct.lim.phi, header + 132, 4 );
    memcpy( &ct.ll,  header +  96, 40 );

    // do some minimal validation to ensure the structure isn't corrupt
    if ( (ct.lim.lam < 1) || (ct.lim.lam > 100000) 
      || (ct.lim.phi < 1) || (ct.lim.phi > 100000) )
    {
        return false;
    }
    
    // trim white space and newlines off id
    boost::trim_right_if(ct.id, is_trimmable_char());

    //ct.cvs.clear();

    gridinfo.push_back(pj_gi(gridname, pj_gi::ctable2));
    gridinfo.back().ct = ct;

    return true;
}

/************************************************************************/
/*                    pj_gridinfo_init_ctable()                         */
/*                                                                      */
/*      Read the header portion of a "ctable" format grid.              */
/************************************************************************/

// Originally nad_ctable_init() defined in nad_init.c
template <typename IStream>
inline bool pj_gridinfo_init_ctable(std::string const& gridname,
                                    IStream & is,
                                    pj_gridinfo & gridinfo)
{
    BOOST_STATIC_ASSERT( sizeof(boost::int32_t) == 4 );
    BOOST_STATIC_ASSERT( sizeof(double) == 8 );

    // 80 + 2*8 + 2*8 + 2*4
    char header[120];

    // NOTE: in proj4 data is loaded directly into CTABLE

    is.read(header, sizeof(header));
    if( is.fail() )
    {
        return false;
    }

    // NOTE: in proj4 LSB is not checked here

    // read the table header
    pj_ctable ct;

    ct.id = std::string(header, std::find(header, header + 80, '\0'));
    memcpy( &ct.ll, header + 80, 40 );

    // do some minimal validation to ensure the structure isn't corrupt
    if ( (ct.lim.lam < 1) || (ct.lim.lam > 100000) 
      || (ct.lim.phi < 1) || (ct.lim.phi > 100000) )
    {
        return false;
    }
    
    // trim white space and newlines off id
    boost::trim_right_if(ct.id, is_trimmable_char());

    //ct.cvs.clear();

    gridinfo.push_back(pj_gi(gridname, pj_gi::ctable));
    gridinfo.back().ct = ct;

    return true;
}

/************************************************************************/
/*                          pj_gridinfo_init()                          */
/*                                                                      */
/*      Open and parse header details from a datum gridshift file       */
/*      returning a list of PJ_GRIDINFOs for the grids in that          */
/*      file.  This superceeds use of nad_init() for modern             */
/*      applications.                                                   */
/************************************************************************/

template <typename IStream>
inline bool pj_gridinfo_init(std::string const& gridname,
                             IStream & is,
                             pj_gridinfo & gridinfo)
{
    char header[160];

    // Check if the stream is opened.
    if (! is.is_open()) {
        return false;
    }

    // Load a header, to determine the file type.
    is.read(header, sizeof(header));

    if ( is.fail() ) {
        return false;
    }
    
    is.seekg(0);

    // Determine file type.
    if ( cstr_equal(header + 0, "HEADER", 6)
      && cstr_equal(header + 96, "W GRID", 6)
      && cstr_equal(header + 144, "TO      NAD83   ", 16) )
    {
        return pj_gridinfo_init_ntv1(gridname, is, gridinfo);
    }
    else if( cstr_equal(header + 0, "NUM_OREC", 8)
          && cstr_equal(header + 48, "GS_TYPE", 7) )
    {
        return pj_gridinfo_init_ntv2(gridname, is, gridinfo);
    }
    else if( boost::algorithm::ends_with(gridname, "gtx")
          || boost::algorithm::ends_with(gridname, "GTX") )
    {
        return pj_gridinfo_init_gtx(gridname, is, gridinfo);
    }
    else if( cstr_equal(header + 0, "CTABLE V2", 9) )
    {
        return pj_gridinfo_init_ctable2(gridname, is, gridinfo);
    }
    else
    {
        return pj_gridinfo_init_ctable(gridname, is, gridinfo);
    }
}


} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDINFO_HPP

/* pj_gridinfo.hpp
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
*/