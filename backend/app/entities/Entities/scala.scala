package entities.Entities

import play.api.libs.json.JsValue

sealed trait HidremoEvent {
  def event: String
}

object HidremoEvent {

  implicit def json2object(value: JsValue): HidremoEvent = {
    ???
  }

  implicit def object2json(event: HidremoEvent): JsValue = {
    ???
  }

}
