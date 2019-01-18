package controllers

import javax.inject.{Inject, Singleton}
import play.api.mvc.{AbstractController, ControllerComponents}
import services.MyKeyEventService

@Singleton
class MyController @Inject()(
  cc: ControllerComponents,
  keyEventService: MyKeyEventService
) extends AbstractController(cc) {

}
