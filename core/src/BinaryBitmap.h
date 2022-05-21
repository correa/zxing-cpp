/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
* Copyright 2021 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ReadBarcode.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace ZXing {

class BitMatrix;

using PatternRow = std::vector<uint16_t>;

/**
* This class is the core bitmap class used by ZXing to represent 1 bit data. Reader objects
* accept a BinaryBitmap and attempt to decode it.
*/
class BinaryBitmap
{
	struct Cache;
	std::unique_ptr<Cache> _cache;

protected:
	const ImageView _buffer;

	/**
	* Converts a 2D array of luminance data to 1 bit (true means black).
	*
	* @return The 2D array of bits for the image, nullptr on error.
	*/
	virtual std::shared_ptr<const BitMatrix> getBlackMatrix() const = 0;

public:
	BinaryBitmap(const ImageView& buffer);
	virtual ~BinaryBitmap();

	int width() const { return _buffer.width(); }
	int height() const { return _buffer.height(); }

	/**
	* Converts one row of luminance data to a vector of ints denoting the widths of the bars and spaces.
	*/
	virtual bool getPatternRow(int row, int rotation, PatternRow& res) const = 0;

	const BitMatrix* getBitMatrix() const;
};

} // ZXing
