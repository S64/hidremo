name := """backend"""
organization := "jp.s64.hidremo"

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayScala)

libraryDependencies += guice

scalaVersion := "2.12.8"
