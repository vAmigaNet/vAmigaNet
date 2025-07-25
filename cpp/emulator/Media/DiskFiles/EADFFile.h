// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "ADFFile.h"

namespace vamiga {

/* This class represents a file in extended ADF format. Layout:
 *
 *   1. Header section:
 *
 *      8 Byte: "UAE-1ADF"
 *      2 Byte: Reserved
 *      2 Byte: Number of tracks (default 2*80=160)
 *
 *   2. Track header section (one entry for each track):
 *
 *      2 Byte: Reserved
 *      2 Byte: Type
 *              0 = standard AmigaDOS track
 *              1 = raw MFM data (upper byte = disk revolutions - 1)
 *      4 Byte: Available space for track in bytes (must be even)
 *      4 Byte: Track length in bits
 *
 *   3. Track data section
 *
 * Note: There is related format with a "UAE--ADF" header. This format had been
 * introduced by Factor 5 to distribute Turrican images and those images seem
 * to be the only ones out there. This format is not supported by the emulator
 * and won't be.
 */

class EADFFile : public FloppyFile {

    // Accepted header signatures
    static const std::vector<string> extAdfHeaders;
    
    // The same file as a standard ADF (if a conversion is possible)
    ADFFile adf;
    
public:

    static bool isCompatible(const fs::path &path);
    static bool isCompatible(const u8 *buf, isize len);
    static bool isCompatible(const Buffer<u8> &buffer);


    //
    // Initializing
    //

public:

    using AnyFile::init;
    
    EADFFile(const fs::path &path) throws { init(path); }
    EADFFile(const u8 *buf, isize len) throws { init(buf, len); }
    EADFFile(class FloppyDisk &disk) throws { init(disk); }
    EADFFile(class FloppyDrive &drive) throws { init(drive); }

    void init(FloppyDisk &disk) throws;
    void init(FloppyDrive &drive) throws;

    
    //
    // Methods from CoreObject
    //

public:
    
    const char *objectName() const override { return "EADF"; }

    
    //
    // Methods from AnyFile
    //
    
public:
    
    FileType type() const override { return FileType::EADF; }
    bool isCompatiblePath(const fs::path &path) const override { return isCompatible(path); }
    bool isCompatibleBuffer(const u8 *buf, isize len) const override { return isCompatible(buf, len); }
    void finalizeRead() throws override;
    
    
    //
    // Methods from DiskFile
    //

    isize numCyls() const override;
    isize numHeads() const override;
    isize numSectors() const override;
    
    
    //
    // Methods from FloppyFile
    //
    
    FSFormat getDos() const override;
    void setDos(FSFormat dos) override { };
    Diameter getDiameter() const override;
    Density getDensity() const override;
    
    u8 readByte(isize b, isize offset) const override { return 0; }
    u8 readByte(isize t, isize s, isize offset) const override { return 0; }
    void readSector(u8 *dst, isize b) const override { }
    void readSector(u8 *dst, isize t, isize s) const override { }
    
    void encodeDisk(class FloppyDisk &disk) const throws override;
    void decodeDisk(const class FloppyDisk &disk) throws override;
    
private:
    
    void encodeStandardTrack(class ADFFile &adf, Track t) const throws;
    void encodeExtendedTrack(class FloppyDisk &disk, Track t) const throws;


    // Scanning the raw data
    //
    
public:
    
    isize storedTracks() const;
    isize typeOfTrack(isize nr) const;
    isize availableBytesForTrack(isize nr) const;
    isize usedBitsForTrack(isize nr) const;
    isize proposedHeaderSize() const;
    isize proposedFileSize() const;
    
    // Returns a pointer to the first data byte of a certain track
    u8 *trackData(isize nr) const;
};

}
