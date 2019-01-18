package controllers

import akka.stream.scaladsl.{Flow, Sink}
import javax.inject.{Inject, Singleton}
import play.api.libs.json.JsValue
import play.api.mvc.{AbstractController, ControllerComponents, WebSocket}
import services.MyKeyEventService

@Singleton
class MyController @Inject()(
  cc: ControllerComponents,
  keyEventService: MyKeyEventService
) extends AbstractController(cc) {

  def ws: WebSocket = WebSocket.accept[JsValue, JsValue] { req =>
    Flow.fromSinkAndSource(Sink.ignore, keyEventService.mySource);
  }

}
