package services

import akka.NotUsed
import akka.stream.scaladsl.{Sink, Source}
import com.google.inject.ImplementedBy
import play.api.libs.json.JsValue

@ImplementedBy(classOf[MyKeyEventServiceImpl])
trait MyKeyEventService {

  val mySink: Sink[JsValue, NotUsed]
  val mySource: Source[JsValue, NotUsed]

  def sendKeyEvent(usage: Int, keyCode: Int)

}

class MyKeyEventServiceImpl extends MyKeyEventService {

  override val mySink: Sink[JsValue, NotUsed] = ???
  override val mySource: Source[JsValue, NotUsed] = ???

  override def sendKeyEvent(usage: Int, keyCode: Int): Unit = ???

}
