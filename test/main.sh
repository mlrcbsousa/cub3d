#!/bin/bash

echo "Error output tests."
./cub3d # no file error
./cub3d invalid.cub # invalid file error

echo "Example file"
./cub3d example.cub
