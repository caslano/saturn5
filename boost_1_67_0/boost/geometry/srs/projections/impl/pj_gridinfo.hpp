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