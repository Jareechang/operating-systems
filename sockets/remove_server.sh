#!/bin/bash

kill $(ps | grep server | awk '{print $1}')
