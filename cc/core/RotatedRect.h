#include "macros.h"
#include <opencv2/core.hpp>
#include "Point.h"
#include "Size.h"
#include "Rect.h"

#ifndef __FF_ROTATEDRECT_H__
#define __FF_ROTATEDRECT_H__

class RotatedRect : public FF::ObjectWrap<RotatedRect, cv::RotatedRect> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "RotatedRect";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	FF_ACCESSORS(angle, FF::FloatConverter);
	FF_ACCESSORS(center, Point2::Converter);
	FF_ACCESSORS(size, Size::Converter);

	static NAN_METHOD(BoundingRect) {
		info.GetReturnValue().Set(Rect::Converter::wrap(unwrapSelf(info).boundingRect()));
	}

	static NAN_METHOD(Points) {
		cv::RotatedRect rotatedRect = unwrapSelf(info);
		cv::Point2f pts2d[4];
		rotatedRect.points(pts2d);
		std::vector<cv::Point2f> jsPts;
		for (int i=0; i<4; i++) {
			jsPts.push_back(pts2d[i]);
		}

		info.GetReturnValue().Set(Point2::ArrayWithCastConverter<cv::Point2f>::wrap(jsPts));
	}
};

#endif