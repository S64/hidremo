package entities.Entities

import play.api.libs.json.{JsValue, Json}

sealed trait HidremoEvent {
  def event: String
}

object HidremoEvent {

  implicit def json2object(value: JsValue): HidremoEvent = {
    (value \ "event").as[String] match {
      case "KeyEvent" => value.as[HidremoKeyEvent]
    }
  }

  implicit def object2json(event: HidremoEvent): JsValue = {
    event match {
      case event: HidremoKeyEvent => Json.toJson(event)
    }
  }

}

case class HidremoKeyEvent(
  event: String,
  usage: Int,
  keyCode: Int
) extends HidremoEvent

object HidremoKeyEvent {

  implicit val format = Json.format[HidremoKeyEvent]

}
