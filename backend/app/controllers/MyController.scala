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

  def togglePower = Action { req =>
    keyEventService.sendKeyEvent(7, 102)
    Ok("Request was sent.")
  }

  def launchTv = Action { req =>
    keyEventService.sendKeyEvent(192, 137)
    Ok("Request was sent.")
  }

  def sleep = Action { req =>
    keyEventService.sendKeyEvent(192, 50)
    Ok("Request was sent.")
  }

  def volumeUp = Action { req =>
    keyEventService.sendKeyEvent(192, 233)
    Ok("Request was sent.")
  }

  def volumeDown = Action { req =>
    keyEventService.sendKeyEvent(192, 234)
    Ok("Request was sent.")
  }

  def numOne = Action { req =>
    keyEventService.sendKeyEvent(7, 30)
    Ok("Request was sent.")
  }

  def numTwo = Action { req =>
    keyEventService.sendKeyEvent(7, 31)
    Ok("Request was sent.")
  }

  def numFour = Action { req =>
    keyEventService.sendKeyEvent(7, 33)
    Ok("Request was sent.")
  }

  def numFive = Action { req =>
    keyEventService.sendKeyEvent(7, 34)
    Ok("Request was sent.")
  }

  def numSix = Action { req =>
    keyEventService.sendKeyEvent(7, 35)
    Ok("Request was sent.")
  }

  def numSeven = Action { req =>
    keyEventService.sendKeyEvent(7, 36)
    Ok("Request was sent.")
  }

  def numEight = Action { req =>
    keyEventService.sendKeyEvent(7, 37)
    Ok("Request was sent.")
  }

  def numNine = Action { req =>
    keyEventService.sendKeyEvent(7, 38)
    Ok("Request was sent.")
  }

}
