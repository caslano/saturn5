//  (C) Copyright Nick Thompson 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_TOOLS_ULP_PLOT_HPP
#define BOOST_MATH_TOOLS_ULP_PLOT_HPP
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <list>
#include <random>
#include <limits>
#include <stdexcept>
#include <boost/math/tools/is_standalone.hpp>
#include <boost/math/tools/condition_numbers.hpp>

#ifndef BOOST_MATH_STANDALONE
#include <boost/random/uniform_real_distribution.hpp>
#endif

// Design of this function comes from:
// https://blogs.mathworks.com/cleve/2017/01/23/ulps-plots-reveal-math-function-accurary/

// The envelope is the maximum of 1/2 and half the condition number of function evaluation.

namespace boost::math::tools {

namespace detail {
template<class F1, class F2, class CoarseReal, class PreciseReal>
void write_gridlines(std::ostream& fs, int horizontal_lines, int vertical_lines,
                     F1 x_scale, F2 y_scale, CoarseReal min_x, CoarseReal max_x, PreciseReal min_y, PreciseReal max_y,
                     int graph_width, int graph_height, int margin_left, std::string const & font_color)
{
  // Make a grid:
  for (int i = 1; i <= horizontal_lines; ++i) {
      PreciseReal y_cord_dataspace = min_y +  ((max_y - min_y)*i)/horizontal_lines;
      auto y = y_scale(y_cord_dataspace);
      fs << "<line x1='0' y1='" << y << "' x2='" << graph_width
         << "' y2='" << y
         << "' stroke='gray' stroke-width='1' opacity='0.5' stroke-dasharray='4' />\n";

      fs << "<text x='" <<  -margin_left/4 + 5 << "' y='" << y - 3
         << "' font-family='times' font-size='10' fill='" << font_color << "' transform='rotate(-90 "
         << -margin_left/4 + 8 << " " << y + 5 << ")'>"
         << std::setprecision(4) << y_cord_dataspace << "</text>\n";
   }

    for (int i = 1; i <= vertical_lines; ++i) {
        CoarseReal x_cord_dataspace = min_x +  ((max_x - min_x)*i)/vertical_lines;
        CoarseReal x = x_scale(x_cord_dataspace);
        fs << "<line x1='" << x << "' y1='0' x2='" << x
           << "' y2='" << graph_height
           << "' stroke='gray' stroke-width='1' opacity='0.5' stroke-dasharray='4' />\n";

        fs << "<text x='" <<  x - 10  << "' y='" << graph_height + 10
           << "' font-family='times' font-size='10' fill='" << font_color << "'>"
           << std::setprecision(4) << x_cord_dataspace << "</text>\n";
    }
}
}

template<class F, typename PreciseReal, typename CoarseReal>
class ulps_plot {
public:
    ulps_plot(F hi_acc_impl, CoarseReal a, CoarseReal b,
             size_t samples = 1000, bool perturb_abscissas = false, int random_seed = -1);

    ulps_plot& clip(PreciseReal clip);

    ulps_plot& width(int width);

    ulps_plot& envelope_color(std::string const & color);

    ulps_plot& title(std::string const & title);

    ulps_plot& background_color(std::string const & background_color);

    ulps_plot& font_color(std::string const & font_color);

    ulps_plot& crop_color(std::string const & color);

    ulps_plot& nan_color(std::string const & color);

    ulps_plot& ulp_envelope(bool write_ulp);

    template<class G>
    ulps_plot& add_fn(G g, std::string const & color = "steelblue");

    ulps_plot& horizontal_lines(int horizontal_lines);

    ulps_plot& vertical_lines(int vertical_lines);

    void write(std::string const & filename) const;

    friend std::ostream& operator<<(std::ostream& fs, ulps_plot const & plot)
    {
        using std::abs;
        using std::floor;
        using std::isnan;
        if (plot.ulp_list_.size() == 0)
        {
            throw std::domain_error("No functions added for comparison.");
        }
        if (plot.width_ <= 1)
        {
            throw std::domain_error("Width = " + std::to_string(plot.width_) + ", which is too small.");
        }

        PreciseReal worst_ulp_distance = 0;
        PreciseReal min_y = (std::numeric_limits<PreciseReal>::max)();
        PreciseReal max_y = std::numeric_limits<PreciseReal>::lowest();
        for (auto const & ulp_vec : plot.ulp_list_)
        {
            for (auto const & ulp : ulp_vec)
            {
                if (static_cast<PreciseReal>(abs(ulp)) > worst_ulp_distance)
                {
                    worst_ulp_distance = static_cast<PreciseReal>(abs(ulp));
                }
                if (static_cast<PreciseReal>(ulp) < min_y)
                {
                    min_y = static_cast<PreciseReal>(ulp);
                }
                if (static_cast<PreciseReal>(ulp) > max_y)
                {
                    max_y = static_cast<PreciseReal>(ulp);
                }
            }
        }

        // half-ulp accuracy is the best that can be expected; sometimes we can get less, but barely less.
        // then the axes don't show up; painful!
        if (max_y < 0.5) {
            max_y = 0.5;
        }
        if (min_y > -0.5) {
            min_y = -0.5;
        }

        if (plot.clip_ > 0)
        {
            if (max_y > plot.clip_)
            {
                max_y = plot.clip_;
            }
            if (min_y < -plot.clip_)
            {
                min_y = -plot.clip_;
            }
        }

        int height = static_cast<int>(floor(double(plot.width_)/1.61803));
        int margin_top = 40;
        int margin_left = 25;
        if (plot.title_.size() == 0)
        {
            margin_top = 10;
            margin_left = 15;
        }
        int margin_bottom = 20;
        int margin_right = 20;
        int graph_height = height - margin_bottom - margin_top;
        int graph_width = plot.width_ - margin_left - margin_right;

        // Maps [a,b] to [0, graph_width]
        auto x_scale = [&](CoarseReal x)->CoarseReal
        {
            return ((x-plot.a_)/(plot.b_ - plot.a_))*static_cast<CoarseReal>(graph_width);
        };

        auto y_scale = [&](PreciseReal y)->PreciseReal
        {
            return ((max_y - y)/(max_y - min_y) )*static_cast<PreciseReal>(graph_height);
        };

        fs << "<?xml version=\"1.0\" encoding='UTF-8' ?>\n"
           << "<svg xmlns='http://www.w3.org/2000/svg' width='"
           << plot.width_ << "' height='"
           << height << "'>\n"
           << "<style>\nsvg { background-color:" << plot.background_color_ << "; }\n"
           << "</style>\n";
        if (plot.title_.size() > 0)
        {
            fs << "<text x='" << floor(plot.width_/2)
               << "' y='" << floor(margin_top/2)
               << "' font-family='Palatino' font-size='25' fill='"
               << plot.font_color_  << "'  alignment-baseline='middle' text-anchor='middle'>"
               << plot.title_
               << "</text>\n";
        }

        // Construct SVG group to simplify the calculations slightly:
        fs << "<g transform='translate(" << margin_left << ", " << margin_top << ")'>\n";
            // y-axis:
        fs  << "<line x1='0' y1='0' x2='0' y2='" << graph_height
            << "' stroke='gray' stroke-width='1'/>\n";
        PreciseReal x_axis_loc = y_scale(static_cast<PreciseReal>(0));
        fs << "<line x1='0' y1='" << x_axis_loc
            << "' x2='" << graph_width << "' y2='" << x_axis_loc
            << "' stroke='gray' stroke-width='1'/>\n";

        if (worst_ulp_distance > 3)
        {
            detail::write_gridlines(fs, plot.horizontal_lines_, plot.vertical_lines_, x_scale, y_scale, plot.a_, plot.b_,
                                    min_y, max_y, graph_width, graph_height, margin_left, plot.font_color_);
        }
        else
        {
            std::vector<double> ys{-3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
            for (size_t i = 0; i < ys.size(); ++i)
            {
                if (min_y <= ys[i] && ys[i] <= max_y)
                {
                    PreciseReal y_cord_dataspace = ys[i];
                    PreciseReal y = y_scale(y_cord_dataspace);
                    fs << "<line x1='0' y1='" << y << "' x2='" << graph_width
                       << "' y2='" << y
                       << "' stroke='gray' stroke-width='1' opacity='0.5' stroke-dasharray='4' />\n";

                    fs << "<text x='" <<  -margin_left/2 << "' y='" << y - 3
                       << "' font-family='times' font-size='10' fill='" << plot.font_color_ << "' transform='rotate(-90 "
                       << -margin_left/2 + 7 << " " << y << ")'>"
                       <<  std::setprecision(4) << y_cord_dataspace << "</text>\n";
                }
            }
            for (int i = 1; i <= plot.vertical_lines_; ++i)
            {
                CoarseReal x_cord_dataspace = plot.a_ +  ((plot.b_ - plot.a_)*i)/plot.vertical_lines_;
                CoarseReal x = x_scale(x_cord_dataspace);
                fs << "<line x1='" << x << "' y1='0' x2='" << x
                   << "' y2='" << graph_height
                   << "' stroke='gray' stroke-width='1' opacity='0.5' stroke-dasharray='4' />\n";

                fs << "<text x='" <<  x - 10  << "' y='" << graph_height + 10
                   << "' font-family='times' font-size='10' fill='" << plot.font_color_ << "'>"
                   << std::setprecision(4) << x_cord_dataspace << "</text>\n";
            }
        }

        int color_idx = 0;
        for (auto const & ulp : plot.ulp_list_)
        {
            std::string color = plot.colors_[color_idx++];
            for (size_t j = 0; j < ulp.size(); ++j)
            {
                if (isnan(ulp[j]))
                {
                    if(plot.nan_color_ == "")
                        continue;
                    CoarseReal x = x_scale(plot.coarse_abscissas_[j]);
                    PreciseReal y = y_scale(static_cast<PreciseReal>(plot.clip_));
                    fs << "<circle cx='" << x << "' cy='" << y << "' r='1' fill='" << plot.nan_color_ << "'/>\n";
                    y = y_scale(static_cast<PreciseReal>(-plot.clip_));
                    fs << "<circle cx='" << x << "' cy='" << y << "' r='1' fill='" << plot.nan_color_ << "'/>\n";
                }
                if (plot.clip_ > 0 && static_cast<PreciseReal>(abs(ulp[j])) > plot.clip_)
                {
                   if (plot.crop_color_ == "")
                      continue;
                   CoarseReal x = x_scale(plot.coarse_abscissas_[j]);
                   PreciseReal y = y_scale(static_cast<PreciseReal>(ulp[j] < 0 ? -plot.clip_ : plot.clip_));
                   fs << "<circle cx='" << x << "' cy='" << y << "' r='1' fill='" << plot.crop_color_ << "'/>\n";
                }
                else
                {
                   CoarseReal x = x_scale(plot.coarse_abscissas_[j]);
                   PreciseReal y = y_scale(static_cast<PreciseReal>(ulp[j]));
                   fs << "<circle cx='" << x << "' cy='" << y << "' r='1' fill='" << color << "'/>\n";
                }
            }
        }

        if (plot.ulp_envelope_)
        {
            std::string close_path = "' stroke='"  + plot.envelope_color_ + "' stroke-width='1' fill='none'></path>\n";
            size_t jstart = 0;
            while (plot.cond_[jstart] > max_y)
            {
                ++jstart;
                if (jstart >= plot.cond_.size())
                {
                    goto done;
                }
            }

            size_t jmin = jstart;
        new_top_path:
            if (jmin >= plot.cond_.size())
            {
                goto start_bottom_paths;
            }
            fs << "<path d='M" << x_scale(plot.coarse_abscissas_[jmin]) << " " << y_scale(plot.cond_[jmin]);

            for (size_t j = jmin + 1; j < plot.coarse_abscissas_.size(); ++j)
            {
                bool bad = isnan(plot.cond_[j]) || (plot.cond_[j] > max_y);
                if (bad)
                {
                    ++j;
                    while ( (j < plot.coarse_abscissas_.size() - 2) && bad)
                    {
                        bad = isnan(plot.cond_[j]) || (plot.cond_[j] > max_y);
                        ++j;
                    }
                    jmin = j;
                    fs << close_path;
                    goto new_top_path;
                }

                CoarseReal t = x_scale(plot.coarse_abscissas_[j]);
                PreciseReal y = y_scale(plot.cond_[j]);
                fs << " L" << t << " " << y;
            }
            fs << close_path;
        start_bottom_paths:
            jmin = jstart;
        new_bottom_path:
            if (jmin >= plot.cond_.size())
            {
                goto done;
            }
            fs << "<path d='M" << x_scale(plot.coarse_abscissas_[jmin]) << " " << y_scale(-plot.cond_[jmin]);

            for (size_t j = jmin + 1; j < plot.coarse_abscissas_.size(); ++j)
            {
                bool bad = isnan(plot.cond_[j]) || (-plot.cond_[j] < min_y);
                if (bad)
                {
                    ++j;
                    while ( (j < plot.coarse_abscissas_.size() - 2) && bad)
                    {
                        bad = isnan(plot.cond_[j]) || (-plot.cond_[j] < min_y);
                        ++j;
                    }
                    jmin = j;
                    fs << close_path;
                    goto new_bottom_path;
                }
                CoarseReal t = x_scale(plot.coarse_abscissas_[j]);
                PreciseReal y = y_scale(-plot.cond_[j]);
                fs << " L" << t << " " << y;
            }
            fs << close_path;
        }
    done:
        fs << "</g>\n"
           << "</svg>\n";
        return fs;
    }

private:
    std::vector<PreciseReal> precise_abscissas_;
    std::vector<CoarseReal> coarse_abscissas_;
    std::vector<PreciseReal> precise_ordinates_;
    std::vector<PreciseReal> cond_;
    std::list<std::vector<CoarseReal>> ulp_list_;
    std::vector<std::string> colors_;
    CoarseReal a_;
    CoarseReal b_;
    PreciseReal clip_;
    int width_;
    std::string envelope_color_;
    bool ulp_envelope_;
    int horizontal_lines_;
    int vertical_lines_;
    std::string title_;
    std::string background_color_;
    std::string font_color_;
    std::string crop_color_;
    std::string nan_color_;
};

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::envelope_color(std::string const & color)
{
    envelope_color_ = color;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::clip(PreciseReal clip)
{
    clip_ = clip;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::width(int width)
{
    width_ = width;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::horizontal_lines(int horizontal_lines)
{
    horizontal_lines_ = horizontal_lines;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::vertical_lines(int vertical_lines)
{
    vertical_lines_ = vertical_lines;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::title(std::string const & title)
{
    title_ = title;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::background_color(std::string const & background_color)
{
    background_color_ = background_color;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::font_color(std::string const & font_color)
{
    font_color_ = font_color;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::crop_color(std::string const & color)
{
    crop_color_ = color;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::nan_color(std::string const & color)
{
    nan_color_ = color;
    return *this;
}

template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::ulp_envelope(bool write_ulp_envelope)
{
    ulp_envelope_ = write_ulp_envelope;
    return *this;
}

namespace detail{
bool ends_with(std::string const& filename, std::string const& suffix)
{
    if(filename.size() < suffix.size())
    {
        return false;
    }

    return std::equal(std::begin(suffix), std::end(suffix), std::end(filename) - suffix.size());
}
}

template<class F, typename PreciseReal, typename CoarseReal>
void ulps_plot<F, PreciseReal, CoarseReal>::write(std::string const & filename) const
{
    if(!boost::math::tools::detail::ends_with(filename, ".svg"))
    {
        throw std::logic_error("Only svg files are supported at this time.");
    }
    std::ofstream fs(filename);
    fs << *this;
    fs.close();
}


template<class F, typename PreciseReal, typename CoarseReal>
ulps_plot<F, PreciseReal, CoarseReal>::ulps_plot(F hi_acc_impl, CoarseReal a, CoarseReal b,
             size_t samples, bool perturb_abscissas, int random_seed) : crop_color_("red")
{
    // Use digits10 for this comparison in case the two types have differeing radixes:
    static_assert(std::numeric_limits<PreciseReal>::digits10 >= std::numeric_limits<CoarseReal>::digits10, "PreciseReal must have higher precision that CoarseReal");
    if (samples < 10)
    {
        throw std::domain_error("Must have at least 10 samples, samples = " + std::to_string(samples));
    }
    if (b <= a)
    {
        throw std::domain_error("On interval [a,b], b > a is required.");
    }
    a_ = a;
    b_ = b;

    std::mt19937_64 gen;
    if (random_seed == -1)
    {
        std::random_device rd;
        gen.seed(rd());
    }

    // Boost's uniform_real_distribution can generate quad and multiprecision random numbers; std's cannot:
    #ifndef BOOST_MATH_STANDALONE
    boost::random::uniform_real_distribution<PreciseReal> dis(static_cast<PreciseReal>(a), static_cast<PreciseReal>(b));
    #else
    // Use std::random in standalone mode if it is a type that the standard library can support (float, double, or long double)
    static_assert(std::numeric_limits<PreciseReal>::digits10 <= std::numeric_limits<long double>::digits10, "Standalone mode does not support types with precision that exceeds long double");
    std::uniform_real_distribution<PreciseReal> dis(static_cast<PreciseReal>(a), static_cast<PreciseReal>(b));
    #endif
    
    precise_abscissas_.resize(samples);
    coarse_abscissas_.resize(samples);

    if (perturb_abscissas)
    {
        for(size_t i = 0; i < samples; ++i)
        {
            precise_abscissas_[i] = dis(gen);
        }
        std::sort(precise_abscissas_.begin(), precise_abscissas_.end());
        for (size_t i = 0; i < samples; ++i)
        {
            coarse_abscissas_[i] = static_cast<CoarseReal>(precise_abscissas_[i]);
        }
    }
    else
    {
        for(size_t i = 0; i < samples; ++i)
        {
            coarse_abscissas_[i] = static_cast<CoarseReal>(dis(gen));
        }
        std::sort(coarse_abscissas_.begin(), coarse_abscissas_.end());
        for (size_t i = 0; i < samples; ++i)
        {
            precise_abscissas_[i] = static_cast<PreciseReal>(coarse_abscissas_[i]);
        }
    }

    precise_ordinates_.resize(samples);
    for (size_t i = 0; i < samples; ++i)
    {
        precise_ordinates_[i] = hi_acc_impl(precise_abscissas_[i]);
    }

    cond_.resize(samples, std::numeric_limits<PreciseReal>::quiet_NaN());
    for (size_t i = 0 ; i < samples; ++i)
    {
        PreciseReal y = precise_ordinates_[i];
        if (y != 0)
        {
            // Maybe cond_ is badly names; should it be half_cond_?
            cond_[i] = boost::math::tools::evaluation_condition_number(hi_acc_impl, precise_abscissas_[i])/2;
            // Half-ULP accuracy is the correctly rounded result, so make sure the envelop doesn't go below this:
            if (cond_[i] < 0.5)
            {
                cond_[i] = 0.5;
            }
        }
        // else leave it as nan.
    }
    clip_ = -1;
    width_ = 1100;
    envelope_color_ = "chartreuse";
    ulp_envelope_ = true;
    horizontal_lines_ = 8;
    vertical_lines_ = 10;
    title_ = "";
    background_color_ = "black";
    font_color_ = "white";
}

template<class F, typename PreciseReal, typename CoarseReal>
template<class G>
ulps_plot<F, PreciseReal, CoarseReal>& ulps_plot<F, PreciseReal, CoarseReal>::add_fn(G g, std::string const & color)
{
    using std::abs;
    size_t samples = precise_abscissas_.size();
    std::vector<CoarseReal> ulps(samples);
    for (size_t i = 0; i < samples; ++i)
    {
        PreciseReal y_hi_acc = precise_ordinates_[i];
        PreciseReal y_lo_acc = static_cast<PreciseReal>(g(coarse_abscissas_[i]));
        PreciseReal absy = abs(y_hi_acc);
        PreciseReal dist = static_cast<PreciseReal>(nextafter(static_cast<CoarseReal>(absy), (std::numeric_limits<CoarseReal>::max)()) - static_cast<CoarseReal>(absy));
        ulps[i] = static_cast<CoarseReal>((y_lo_acc - y_hi_acc)/dist);
    }
    ulp_list_.emplace_back(ulps);
    colors_.emplace_back(color);
    return *this;
}




} // namespace boost::math::tools
#endif

/* ulps_plot.hpp
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
*/