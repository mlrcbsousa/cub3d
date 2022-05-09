#!/bin/bash

echo "Error output tests."
./cub3d # no file error
./cub3d ./assets/maps/invalid.cub # invalid file error

echo "Example file"
./cub3d ./assets/maps/example.cub
