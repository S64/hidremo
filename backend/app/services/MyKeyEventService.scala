package services

import akka.NotUsed
import akka.stream.Materializer
import akka.stream.scaladsl.{BroadcastHub, Keep, MergeHub, Sink, Source}
import com.google.inject.ImplementedBy
import javax.inject.Inject
import play.api.libs.json.JsValue

@ImplementedBy(classOf[MyKeyEventServiceImpl])
trait MyKeyEventService {

  val mySink: Sink[JsValue, NotUsed]
  val mySource: Source[JsValue, NotUsed]

  def sendKeyEvent(usage: Int, keyCode: Int)

}

class MyKeyEventServiceImpl @Inject()(
  implicit mat: Materializer
) extends MyKeyEventService {

  override val (mySink, mySource) = {
    MergeHub.source[JsValue]
      .toMat(BroadcastHub.sink[JsValue])(Keep.both)
      .run()
  }

  override def sendKeyEvent(usage: Int, keyCode: Int): Unit = ???

}
