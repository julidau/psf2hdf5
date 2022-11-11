# psf2hdf5
A simple PSF waveform data to HDF5 converter

For now just an experiement to test, whether...

1. The HDF5 format can be useful
2. The HDF5 format is equally efficient compared to psf storage-wise
3. the conversion process can be performed in acceptable time for large datasets

This program is so trivial, that i am not even sure a release is useful, but maybe it can be extended.

### Dependencies

Uses "HighFive" and "libpsf", both projects are cloned with cmake using the `FetchContent`-Module
