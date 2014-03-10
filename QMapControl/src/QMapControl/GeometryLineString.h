/*
*
* This file is part of QMapControl,
* an open-source cross-platform map widget
*
* Copyright (C) 2007 - 2008 Kai Winter
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with QMapControl. If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: kaiwinter@gmx.de
* Program URL   : http://qmapcontrol.sourceforge.net/
*
*/

#pragma once

// STL includes.
#include <memory>

// Local includes.
#include "qmapcontrol_global.h"
#include "GeometryCurve.h"
#include "GeometryPoint.h"

namespace qmapcontrol
{
    //! A collection of Point objects to describe a line.
    /*!
     * A LineString is a Curve with linear interpolation between Points. Each consecutive pair of Points defines a Line segment.
     *
     * @author Kai Winter <kaiwinter@gmx.de>
     * @author Chris Stylianou <chris5287@gmail.com>
     */
    class QMAPCONTROL_EXPORT GeometryLineString : public GeometryCurve
    {
        Q_OBJECT
    public:
        //! Constructor.
        /*!
         * The constructor of a LineString takes a list of points to form a line.
         * @param points The list of Geometry Points.
         * @param pen The pen to draw with.
         * @param zoom_minimum The minimum zoom level to show this geometry at.
         * @param zoom_maximum The maximum zoom level to show this geometry at.
         */
        GeometryLineString(const std::vector<std::shared_ptr<GeometryPoint>>& points, const QPen& pen = QPen(), const int& zoom_minimum = 0, const int& zoom_maximum = 17);

        //! Disable copy constructor.
        ///GeometryLineString(const GeometryLineString&) = delete; @todo re-add once MSVC supports default/delete syntax.

        //! Disable copy assignment.
        ///GeometryLineString& operator=(const GeometryLineString&) = delete; @todo re-add once MSVC supports default/delete syntax.

        //! Destructor.
        virtual ~GeometryLineString() { } /// = default; @todo re-add once MSVC supports default/delete syntax.

        /*!
         * Fetches the list of points that form a line.
         * @return the list of points that form a line.
         */
        std::vector<std::shared_ptr<GeometryPoint>> points() const;

        /*!
         * Add a point to the end of the line.
         * @param point The point to add to the end of the line.
         */
        void addPoint(const std::shared_ptr<GeometryPoint>& point);

        /*!
         * Sets the points to use for the LineString.
         * @param points The points to use for the LineString.
         */
        void setPoints(const std::vector<std::shared_ptr<GeometryPoint>>& points);

        /*!
         * When a mouse press event touches points within a LineString,
         * this function contains the points that were actually touched.
         * @return the points that were touched.
         */
        std::vector<std::shared_ptr<GeometryPoint>> touchedPoints() const;

    public:
        /*!
         * The bounding box in world coordinates.
         * @param controller_zoom The current controller zoom.
         * @return the bounding box.
         */
        virtual QRectF boundingBox(const int& controller_zoom) const final;

        /*!
         * Checks if any geometries are located inside the specified area.
         * @param area_px The polygon area in pixels to check for points.
         * @param controller_zoom The current controller zoom.
         * @return whether the geometries are located inside the specified area.
         */
        virtual bool touches(const QGraphicsItem& area_px, const int& controller_zoom) override;

        /*!
         * Draws the geometry to a pixmap using the provided painter.
         * @param painter The painter that will draw to the pixmap.
         * @param backbuffer_rect_px Only draw geometries that are contained in the backbuffer rect (pixels).
         * @param controller_zoom The current controller zoom.
         */
        virtual void draw(QPainter* painter, const QRectF& backbuffer_rect_px, const int& controller_zoom) override;

    private:
        //! Disable copy constructor.
        GeometryLineString(const GeometryLineString&); /// @todo remove once MSVC supports default/delete syntax.

        //! Disable copy assignment.
        GeometryLineString& operator=(const GeometryLineString&); /// @todo remove once MSVC supports default/delete syntax.

    private:
        /// The points that the linestring is made up of.
        std::vector<std::shared_ptr<GeometryPoint>>	m_points;

        /// The points that were touched on the last mouse press event.
        std::vector<std::shared_ptr<GeometryPoint>> m_touched_points;
    };
}